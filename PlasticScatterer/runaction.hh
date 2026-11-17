#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"

#include "analysis.hh"

class G4Run;

class runaction : public G4UserRunAction
{
public:

    runaction();
    virtual ~runaction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

    void CountIncident();
    void CountCompton();
    void CountRayleigh();
    void CountPhoto();
    void CountTransmit();

    // Give other classes access to Analysis
    analysis* GetAnalysis();

private:

    G4int nIncident;
    G4int nCompton;
    G4int nRayleigh;
    G4int nPhoto;
    G4int nTransmit;

    analysis analysisManager;
};

#endif