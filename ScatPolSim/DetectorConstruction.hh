#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4GenericMessenger;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

    DetectorConstruction();
    ~DetectorConstruction() override;

    G4VPhysicalVolume* Construct() override;

    // Macro command
    void SetArmPosition(G4double pos);

private:

    void DefineMaterials();
    void DefineCommands();

    //-------------------------
    // Geometry
    //-------------------------

    G4double fScintRadius;
    G4double fScintHalfLength;

    G4double fCollOuterRadius;
    G4double fCollInnerRadius;
    G4double fCollHalfLength;

    G4double fCdTeSideX;
    G4double fCdTeSideY;
    G4double fCdTeHalfThick;

    G4double fScatteringAngleDeg;
    G4double fArmDistance;

    // Distance from scintillator front face
    G4double fArmPosition;

    //-------------------------
    // Geometry pointers
    //-------------------------

    G4LogicalVolume* fScintLogical;

    G4VPhysicalVolume* fScintPhysical;
    G4VPhysicalVolume* fCollPhysical;
    G4VPhysicalVolume* fCdTePhysical;

    G4LogicalVolume* fWorldLogical;

    //-------------------------
    // Messenger
    //-------------------------

    G4GenericMessenger* fMessenger;
};

#endif