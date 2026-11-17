#include "PhysicsList.hh"

#include "G4EmLivermorePolarizedPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4SystemOfUnits.hh"

PhysicsList::PhysicsList()
: G4VModularPhysicsList()
{
  // Polarization-sensitive EM physics (Compton, photoelectric, Rayleigh)
  // — same as used in scatPol01/02 — essential for the asymmetry signal.
  RegisterPhysics(new G4EmLivermorePolarizedPhysics());

  // Standard particle decay (needed for general consistency, e.g. muons
  // if ever introduced, and required by RadioactiveDecayPhysics below).
  RegisterPhysics(new G4DecayPhysics());

  // Radioactive decay physics: lets you later switch from a mono-energetic
  // 59.541 keV gun to an actual Am-241 GeneralParticleSource decay chain
  // if you want full source realism instead of a fixed line.
  RegisterPhysics(new G4RadioactiveDecayPhysics());

  // Optical photon generation/transport in the scintillator
  // (scintillation + Cerenkov + boundary processes).
  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  RegisterPhysics(opticalPhysics);

  // Default production cut. 59.5 keV gammas in plastic/CdTe produce
  // short-range secondaries, so a small default cut is used; the
  // region-specific cuts below tighten it further around the CdTe.
  SetDefaultCutValue(0.1*mm);
}

PhysicsList::~PhysicsList() {}

void PhysicsList::ConstructParticle()
{
  G4VModularPhysicsList::ConstructParticle();
}

void PhysicsList::ConstructProcess()
{
  G4VModularPhysicsList::ConstructProcess();
}

void PhysicsList::SetCuts()
{
  // A tighter cut in the CdTe volume would normally be set via
  // G4Region + G4ProductionCuts once a region is registered in
  // DetectorConstruction. For now we just apply the global default cut
  // set in the constructor; we can add a dedicated CdTe region cut
  // later if energy-deposition resolution near the surface matters.
  G4VModularPhysicsList::SetCuts();
}