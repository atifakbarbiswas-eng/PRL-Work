#ifndef SCATTERERSD_HH
#define SCATTERERSD_HH

#include "G4VSensitiveDetector.hh"

class G4Step;
class G4TouchableHistory;

class scattererSD : public G4VSensitiveDetector
{
public:

    scattererSD(const G4String& name);
    virtual ~scattererSD();

    virtual G4bool ProcessHits(G4Step*,
                               G4TouchableHistory*);

};

#endif