#include "scattererSD.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4TouchableHistory.hh"
#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

scattererSD::scattererSD(const G4String& name)
    : G4VSensitiveDetector(name)
{
}

scattererSD::~scattererSD()
{
}

G4bool scattererSD::ProcessHits(G4Step* step,
                                G4TouchableHistory*)
{
    // Only record the primary gamma
    if (step->GetTrack()->GetTrackID() != 1)
        return false;

    // Process responsible for this step
    const G4VProcess* process =
        step->GetPostStepPoint()->GetProcessDefinedStep();

    if (!process)
        return false;

    // Print process name
    G4cout << "----------------------------------" << G4endl;
    G4cout << "Process : "
           << process->GetProcessName()
           << G4endl;

    // Print kinetic energy
    G4cout << "Energy : "
           << step->GetPreStepPoint()->GetKineticEnergy()/keV
           << " keV"
           << G4endl;

    // Print interaction position
    G4ThreeVector pos =
        step->GetPostStepPoint()->GetPosition();

    G4cout << "Position : ("
           << pos.x()/cm << ", "
           << pos.y()/cm << ", "
           << pos.z()/cm << ") cm"
           << G4endl;

    G4cout << "----------------------------------" << G4endl;

    return true;
}