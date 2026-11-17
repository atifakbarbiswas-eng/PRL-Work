#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

class G4Step;
class runaction;
class eventaction;
class analysis;

class steppingaction : public G4UserSteppingAction
{
public:

    steppingaction(runaction* run,
                   eventaction* event,
                   analysis* ana);

    virtual ~steppingaction();

    virtual void UserSteppingAction(const G4Step*);

private:

    runaction* fRunAction;
    eventaction* fEventAction;
    analysis* fAnalysis;
};

#endif