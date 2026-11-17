#ifndef PARTICLEGUN_HH
#define PARTICLEGUN_HH

#include "G4VUserPrimaryGeneratorAction.hh"

class G4ParticleGun;
class G4Event;

class particlegun : public G4VUserPrimaryGeneratorAction
{
public:

    particlegun();
    virtual ~particlegun();

    virtual void GeneratePrimaries(G4Event*);

private:

    G4ParticleGun* particleGun;

};

#endif
