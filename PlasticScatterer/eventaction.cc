#include "eventaction.hh"

#include "G4Event.hh"

eventaction::eventaction()
{
    interactionRecorded = false;
}

eventaction::~eventaction()
{
}

void eventaction::BeginOfEventAction(const G4Event*)
{
    // Reset for every new primary gamma
    interactionRecorded = false;
}

void eventaction::EndOfEventAction(const G4Event*)
{
}

//--------------------------------------
// Set interaction flag
//--------------------------------------

void eventaction::SetInteractionRecorded(bool value)
{
    interactionRecorded = value;
}

//--------------------------------------
// Get interaction flag
//--------------------------------------

bool eventaction::GetInteractionRecorded() const
{
    return interactionRecorded;
}