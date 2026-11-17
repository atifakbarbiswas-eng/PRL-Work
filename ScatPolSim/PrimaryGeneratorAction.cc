#include "PrimaryGeneratorAction.hh"

#include "G4GeneralParticleSource.hh"
#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4UImanager.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fGPS(nullptr)
{
    fGPS = new G4GeneralParticleSource();

    G4UImanager* UI = G4UImanager::GetUIpointer();

    // Particle
    UI->ApplyCommand("/gps/particle gamma");

    // Position
    UI->ApplyCommand("/gps/pos/type Point");
    UI->ApplyCommand("/gps/pos/centre 0 0 -20 cm");

    // Direction
    UI->ApplyCommand("/gps/direction 0 0 1");

    // Energy
    UI->ApplyCommand("/gps/ene/type Mono");
    UI->ApplyCommand("/gps/energy 59.541 keV");

    // Polarization
    UI->ApplyCommand("/gps/polarization 1 0 0");
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fGPS;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    fGPS->GeneratePrimaryVertex(event);
}