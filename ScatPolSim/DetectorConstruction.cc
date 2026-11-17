#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4RunManager.hh"

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction(),
   fScintRadius(2.75*cm),
   fScintHalfLength(3.5*cm),

   fCollOuterRadius(1.0*cm),
   fCollInnerRadius(3.75*mm),
   fCollHalfLength(2.5*cm),

   fCdTeSideX(3.75*mm),
   fCdTeSideY(3.75*mm),
   fCdTeHalfThick(0.5*mm),

   fScatteringAngleDeg(90.*deg),
   fArmDistance(3.5*cm),

   // Distance from FRONT FACE of scintillator
   fArmPosition(30.*mm),

   fScintLogical(nullptr),
   fScintPhysical(nullptr),

   fCollPhysical(nullptr),
   fCdTePhysical(nullptr),

   fMessenger(nullptr),
   fWorldLogical(nullptr)
{
    DefineCommands();
}

DetectorConstruction::~DetectorConstruction()
{
    delete fMessenger;
}

void DetectorConstruction::DefineCommands()
{
    fMessenger = new G4GenericMessenger(
        this,
        "/scatPol/arm/",
        "CdTe arm control");

    fMessenger->DeclareMethodWithUnit(
        "setPosition",
        "mm",
        &DetectorConstruction::SetArmPosition,
        "Distance from the FRONT FACE of the scintillator.");
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    DefineMaterials();

    auto nist = G4NistManager::Instance();

    auto worldMat =
        nist->FindOrBuildMaterial("G4_AIR");

    auto scintMat =
        nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");

    auto collMat =
        nist->FindOrBuildMaterial("G4_Pb");

    auto cdteMat =
        nist->FindOrBuildMaterial("G4_CADMIUM_TELLURIDE");

    //----------------------------------------------------
    // World
    //----------------------------------------------------

    auto solidWorld =
        new G4Box(
            "World",
            50*cm,
            50*cm,
            50*cm);

    fWorldLogical =
        new G4LogicalVolume(
            solidWorld,
            worldMat,
            "World");

    fWorldLogical->SetVisAttributes(
        G4VisAttributes::GetInvisible());

    auto physWorld =
        new G4PVPlacement(
            nullptr,
            G4ThreeVector(),
            fWorldLogical,
            "World",
            nullptr,
            false,
            0);

    //----------------------------------------------------
    // Plastic scintillator
    //----------------------------------------------------

    auto solidScint =
        new G4Tubs(
            "Scintillator",
            0.,
            fScintRadius,
            fScintHalfLength,
            0.,
            360.*deg);

    fScintLogical =
        new G4LogicalVolume(
            solidScint,
            scintMat,
            "Scintillator");

    auto scintVis =
        new G4VisAttributes(
            G4Colour(0.2,0.6,1.0,0.4));

    scintVis->SetForceSolid(true);

    fScintLogical->SetVisAttributes(scintVis);

    fScintPhysical =
        new G4PVPlacement(
            nullptr,
            G4ThreeVector(),
            fScintLogical,
            "Scintillator",
            fWorldLogical,
            false,
            0);
    //----------------------------------------------------
    // Fixed 90° CdTe arm
    //----------------------------------------------------

    // X positions are fixed.
    // Only Z changes when the macro command is used.

    G4double xColl =
        fScintRadius +
        fCollHalfLength;

    G4double xCdTe =
        fScintRadius +
        2.*fCollHalfLength +
        fCdTeHalfThick;

    // Front face of scintillator is at +Z
    // Position measured inward from front face.

    G4double zPos =
        fScintHalfLength -
        fArmPosition;

    auto armRot = new G4RotationMatrix();
    armRot->rotateY(-90.*deg);

    //----------------------------------------------------
    // Collimator
    //----------------------------------------------------

    auto solidColl =
        new G4Tubs(
            "Collimator",
            fCollInnerRadius,
            fCollOuterRadius,
            fCollHalfLength,
            0.,
            360.*deg);

    auto collLogical =
        new G4LogicalVolume(
            solidColl,
            collMat,
            "Collimator");

    auto collVis =
        new G4VisAttributes(
            G4Colour(0.6,0.6,0.6));

    collVis->SetForceSolid(true);

    collLogical->SetVisAttributes(collVis);

    fCollPhysical =
        new G4PVPlacement(
            armRot,
            G4ThreeVector(
                xColl,
                0.,
                zPos),
            collLogical,
            "Collimator",
            fWorldLogical,
            false,
            0);

    //----------------------------------------------------
    // CdTe detector
    //----------------------------------------------------

    auto solidCdTe =
        new G4Box(
            "CdTe",
            fCdTeSideX/2.,
            fCdTeSideY/2.,
            fCdTeHalfThick);

    auto cdteLogical =
        new G4LogicalVolume(
            solidCdTe,
            cdteMat,
            "CdTe");

    auto cdteVis =
        new G4VisAttributes(
            G4Colour(1.0,0.6,0.0));

    cdteVis->SetForceSolid(true);

    cdteLogical->SetVisAttributes(cdteVis);

    fCdTePhysical =
        new G4PVPlacement(
            armRot,
            G4ThreeVector(
                xCdTe,
                0.,
                zPos),
            cdteLogical,
            "CdTe",
            fWorldLogical,
            false,
            0);

    return physWorld;
}
void DetectorConstruction::DefineMaterials()
{
    // All materials are taken directly from the NIST database.
    G4NistManager::Instance();
}

void DetectorConstruction::SetArmPosition(G4double pos)
{
    fArmPosition = pos;

    // Fixed X positions
    G4double xColl =
        fScintRadius +
        fCollHalfLength;

    G4double xCdTe =
        fScintRadius +
        2.*fCollHalfLength +
        fCdTeHalfThick;

    // Move only along the scintillator axis (Z)
    G4double zPos =
        fScintHalfLength -
        fArmPosition;

    if (fCollPhysical)
    {
        fCollPhysical->SetTranslation(
            G4ThreeVector(
                xColl,
                0.,
                zPos));
    }

    if (fCdTePhysical)
    {
        fCdTePhysical->SetTranslation(
            G4ThreeVector(
                xCdTe,
                0.,
                zPos));
    }

    G4RunManager::GetRunManager()->GeometryHasBeenModified();

    G4cout << "\n========================================\n";
    G4cout << "CdTe arm position : "
           << fArmPosition/mm
           << " mm from front face\n";

    G4cout << "Collimator centre : ("
           << xColl/cm << ", "
           << 0.0 << ", "
           << zPos/cm << ") cm\n";

    G4cout << "CdTe centre       : ("
           << xCdTe/cm << ", "
           << 0.0 << ", "
           << zPos/cm << ") cm\n";

    G4cout << "========================================\n";
}