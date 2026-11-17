#include "physics.hh"

#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmLivermorePhysics.hh"

physics::physics()
{
    RegisterPhysics(new G4DecayPhysics());

    RegisterPhysics(new G4RadioactiveDecayPhysics());

    RegisterPhysics(new G4EmLivermorePhysics());
}

physics::~physics()
{
}