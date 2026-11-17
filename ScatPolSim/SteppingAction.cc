#include "SteppingAction.hh"

#include "EventAction.hh"

#include "G4Step.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4Gamma.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"

SteppingAction::SteppingAction(EventAction* eventAction)
    : G4UserSteppingAction(),
      fEventAction(eventAction)
{
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    // Energy deposited in this step
    G4double edep = step->GetTotalEnergyDeposit();

    // Current volume
    G4VPhysicalVolume* volume =
        step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();

    G4String volumeName = volume->GetName();

    // Accumulate energy deposition
    if (edep > 0.)
    {
        if (volumeName == "Scintillator")
        {
            fEventAction->AddScintEdep(edep);
        }
        else if (volumeName == "CdTe")
        {
            fEventAction->AddCdTeEdep(edep);
        }
    }
}