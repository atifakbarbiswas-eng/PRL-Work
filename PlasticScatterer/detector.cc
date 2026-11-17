#include "detector.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4SystemOfUnits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "scattererSD.hh"
#include "G4SDManager.hh"

detector::detector()
{
}

detector::~detector()
{
}

G4VPhysicalVolume* detector::Construct()
{
    //-----------------------------
    // NIST Manager
    //-----------------------------

    G4NistManager* nist = G4NistManager::Instance();

    //-----------------------------
    // World Material
    //-----------------------------

    G4Material* worldMaterial =
        nist->FindOrBuildMaterial("G4_AIR");

    //-----------------------------
    // PVT Material
    //-----------------------------

    G4Element* H =
        nist->FindOrBuildElement("H");

    G4Element* C =
        nist->FindOrBuildElement("C");

    G4Material* PVT =
        new G4Material(
            "PVT",
            1.032*g/cm3,
            2);

    PVT->AddElement(C,0.9147);
    PVT->AddElement(H,0.0853);

    //-----------------------------
    // World
    //-----------------------------

    G4double worldSize = 1.0*m;

    auto solidWorld =
        new G4Box(
            "World",
            worldSize/2,
            worldSize/2,
            worldSize/2);

    auto logicWorld =
        new G4LogicalVolume(
            solidWorld,
            worldMaterial,
            "World");

    auto physWorld =
        new G4PVPlacement(
            nullptr,
            G4ThreeVector(),
            logicWorld,
            "World",
            nullptr,
            false,
            0,
            true);

    //-----------------------------
    // Plastic Scatterer
    //-----------------------------

    G4double radius = 2.75*cm;
    G4double length = 7.0*cm;

    auto solidScatterer =
        new G4Tubs(
            "Scatterer",
            0.0*cm,
            radius,
            length/2,
            0.*deg,
            360.*deg);

    auto logicScatterer =
        new G4LogicalVolume(
            solidScatterer,
            PVT,
            "Scatterer");

    new G4PVPlacement(
        nullptr,
        G4ThreeVector(0,0,0),
        logicScatterer,
        "Scatterer",
        logicWorld,
        false,
        0,
        true);

    //-----------------------------
    // Visualization
    //-----------------------------

    auto scatterVis =
        new G4VisAttributes(
            G4Colour(0.0,0.8,1.0));

    scatterVis->SetForceSolid(true);

    logicScatterer->SetVisAttributes(scatterVis);

    logicWorld->SetVisAttributes(
        G4VisAttributes::GetInvisible());
//-----------------------------
// Sensitive Detector
//-----------------------------

G4SDManager* SDman =
    G4SDManager::GetSDMpointer();

scattererSD* scatterSD =
    new scattererSD("ScattererSD");

SDman->AddNewDetector(scatterSD);

logicScatterer->SetSensitiveDetector(scatterSD);

    return physWorld;
}