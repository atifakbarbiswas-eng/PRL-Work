#include "RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"

RunAction::RunAction()
: G4UserRunAction()
{
    auto analysisManager = G4AnalysisManager::Instance();

    analysisManager->SetVerboseLevel(1);

    // No ntuple -> no need for ntuple merging
    analysisManager->SetFileName("ScatPolSim.root");

    // -----------------------------
    // Histograms
    // -----------------------------

    // id 0: CdTe spectrum (No Coincidence)
    analysisManager->CreateH1(
        "CdTe_NC",
        "CdTe energy spectrum (NC)",
        400,
        0.,
        200.);

    // id 1: CdTe spectrum (With Coincidence)
    analysisManager->CreateH1(
        "CdTe_WC",
        "CdTe energy spectrum (WC)",
        400,
        0.,
        200.);

    // id 2: Scintillator deposited energy
    analysisManager->CreateH1(
        "Scint_Edep",
        "Scintillator energy deposit",
        400,
        0.,
        200.);
}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
    G4cout << "### Run "
           << run->GetRunID()
           << " start, "
           << run->GetNumberOfEventToBeProcessed()
           << " events"
           << G4endl;

    auto analysisManager = G4AnalysisManager::Instance();
    analysisManager->OpenFile();
}

void RunAction::EndOfRunAction(const G4Run* run)
{
    auto analysisManager = G4AnalysisManager::Instance();

    analysisManager->Write();
    analysisManager->CloseFile();

    if (!IsMaster())
        return;

    G4int nofEvents = run->GetNumberOfEvent();

    if (nofEvents == 0)
        return;

    G4cout << "\n=========================================\n";
    G4cout << "Run " << run->GetRunID() << " completed.\n";
    G4cout << "Processed events : " << nofEvents << "\n";
    G4cout << "Output file      : "
           << analysisManager->GetFileName() << "\n";
    G4cout << "=========================================\n";
}