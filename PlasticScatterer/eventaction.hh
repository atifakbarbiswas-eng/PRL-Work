#ifndef EVENTACTION_HH
#define EVENTACTION_HH

#include "G4UserEventAction.hh"

class G4Event;

class eventaction : public G4UserEventAction
{
public:

    eventaction();
    virtual ~eventaction();

    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    // First interaction flag
    void SetInteractionRecorded(bool value);
    bool GetInteractionRecorded() const;

private:

    bool interactionRecorded;
};

#endif