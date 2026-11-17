#include "steppingaction.hh"

#include "runaction.hh"
#include "eventaction.hh"
#include "analysis.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4StepPoint.hh"
#include "G4TouchableHandle.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VProcess.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"

#include "G4SystemOfUnits.hh"

steppingaction::steppingaction(runaction* run,
                               eventaction* event,
                               analysis* ana)
{
    fRunAction = run;
    fEventAction = event;
    fAnalysis = ana;
}

steppingaction::~steppingaction()
{
}

void steppingaction::UserSteppingAction(const G4Step* step)
{
    //-------------------------------------------------
    // Only primary gamma
    //-------------------------------------------------

    if(step->GetTrack()->GetTrackID() != 1)
        return;

    //-------------------------------------------------
    // Count incident photon
    //-------------------------------------------------

    if(step->GetTrack()->GetCurrentStepNumber() == 1)
        fRunAction->CountIncident();

    //-------------------------------------------------
    // Already recorded first interaction?
    //-------------------------------------------------

    if(fEventAction->GetInteractionRecorded())
        return;

    //-------------------------------------------------
    // Only inside scatterer
    //-------------------------------------------------

    G4VPhysicalVolume* volume =
        step->GetPreStepPoint()
            ->GetTouchableHandle()
            ->GetVolume();

    if(!volume)
        return;

    if(volume->GetName() != "Scatterer")
        return;

    //-------------------------------------------------
    // Process
    //-------------------------------------------------

    const G4VProcess* process =
        step->GetPostStepPoint()
            ->GetProcessDefinedStep();

    if(!process)
        return;

    G4String name =
        process->GetProcessName();

    //-------------------------------------------------
    // Ignore transportation
    //-------------------------------------------------

    if(name == "Transportation")
        return;

    //-------------------------------------------------
    // Interaction position
    //-------------------------------------------------

    G4ThreeVector pos =
        step->GetPostStepPoint()->GetPosition();

    G4double x = pos.x()/cm;
    G4double y = pos.y()/cm;
    G4double z = pos.z()/cm;

    // Cylinder entrance is at z = -3.5 cm
    G4double depth = z + 3.5;

    //-------------------------------------------------
    // Event ID
    //-------------------------------------------------

    G4int eventID =
        G4RunManager::GetRunManager()
            ->GetCurrentEvent()
            ->GetEventID();

    //-------------------------------------------------
    // Count process
    //-------------------------------------------------

    std::string processName;

    if(name == "compt")
    {
        fRunAction->CountCompton();
        processName = "Compton";
    }
    else if(name == "Rayl")
    {
        fRunAction->CountRayleigh();
        processName = "Rayleigh";
    }
    else if(name == "phot")
    {
        fRunAction->CountPhoto();
        processName = "Photoelectric";
    }
    else
    {
        processName = name;
    }

    //-------------------------------------------------
    // Write interaction to CSV
    //-------------------------------------------------

    fAnalysis->WriteInteraction(
        eventID,
        59.54,
        x,
        y,
        z,
        depth,
        processName);

    //-------------------------------------------------
    // Mark first interaction recorded
    //-------------------------------------------------

    fEventAction->SetInteractionRecorded(true);

    //-------------------------------------------------
    // Kill primary photon
    //-------------------------------------------------

   
