#include "EventAction.hh"

#include "G4Event.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

// Coincidence threshold: 1 keV deposited energy
G4double EventAction::fCoincThreshold = 1.0 * keV;

EventAction::EventAction()
: G4UserEventAction(),
  fScintEdep(0.),
  fCdTeEdep(0.)
{
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
    fScintEdep = 0.;
    fCdTeEdep  = 0.;
}

void EventAction::EndOfEventAction(const G4Event* /*event*/)
{
    auto analysisManager = G4AnalysisManager::Instance();

    G4bool scintHit = (fScintEdep > fCoincThreshold);
    G4bool cdteHit  = (fCdTeEdep  > fCoincThreshold);
    G4bool coincidence = scintHit && cdteHit;

    G4double scintEdep_keV = fScintEdep / keV;
    G4double cdteEdep_keV  = fCdTeEdep  / keV;

    // Fill scintillator histogram
    if (scintHit)
    {
        analysisManager->FillH1(2, scintEdep_keV);
    }

    // Fill CdTe histograms
    if (cdteHit)
    {
        if (coincidence)
        {
            analysisManager->FillH1(1, cdteEdep_keV); // WC
        }
        else
        {
            analysisManager->FillH1(0, cdteEdep_keV); // NC
        }
    }
}