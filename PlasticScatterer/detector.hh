#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;

class detector : public G4VUserDetectorConstruction
{
public:

    detector();
    virtual ~detector();

    virtual G4VPhysicalVolume* Construct();

};

#endif