#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class G4Event;

class EventAction : public G4UserEventAction
{
public:
    EventAction();
    ~EventAction() override;

    void BeginOfEventAction(const G4Event* event) override;
    void EndOfEventAction(const G4Event* event) override;

    // Called by SteppingAction
    void AddScintEdep(G4double edep) { fScintEdep += edep; }
    void AddCdTeEdep(G4double edep)  { fCdTeEdep += edep; }

private:
    G4double fScintEdep;
    G4double fCdTeEdep;

    // Minimum energy deposit required to count as a hit
    static G4double fCoincThreshold;
};

#endif