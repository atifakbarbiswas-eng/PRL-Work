#include "particlegun.hh"

#include "G4ParticleGun.hh"
#include "G4Gamma.hh"
#include "G4Event.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include <cmath>

particlegun::particlegun()
{
    particleGun = new G4ParticleGun(1);

    particleGun->SetParticleDefinition(
        G4Gamma::Gamma());

    particleGun->SetParticleEnergy(
        59.54*keV);

    // Parallel beam along +Z
    particleGun->SetParticleMomentumDirection(
        G4ThreeVector(0.,0.,1.));
}

particlegun::~particlegun()
{
    delete particleGun;
}

void particlegun::GeneratePrimaries(G4Event* event)
{
    // Beam radius = 0.5 mm (Diameter = 1 mm)
    G4double beamRadius = 0.5*mm;

    // Uniform random point inside a circle
    G4double r =
        beamRadius*std::sqrt(G4UniformRand());

    G4double phi =
        2.*CLHEP::pi*G4UniformRand();

    G4double x = r*std::cos(phi);
    G4double y = r*std::sin(phi);
    G4double z = -10.*cm;

    particleGun->SetParticlePosition(
        G4ThreeVector(x,y,z));

    particleGun->GeneratePrimaryVertex(event);
}