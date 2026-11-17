#include "G4RunManagerFactory.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#include "G4UImanager.hh"
#include "particlegun.hh"
#include "detector.hh"
#include "physics.hh"
#include "runaction.hh"
#include "eventaction.hh"
#include "steppingaction.hh"
#include "actioninitialization.hh"

int main(int argc,char** argv)
{
    auto* runManager =
        G4RunManagerFactory::CreateRunManager(
            G4RunManagerType::Default);
    runManager->SetNumberOfThreads(1);

    runManager->SetUserInitialization(
        new detector());

    runManager->SetUserInitialization(
        new physics());
    
    runManager->SetUserInitialization(
    new actioninitialization());

    runManager->Initialize();

    auto* visManager = new G4VisExecutive;
    visManager->Initialize();

    auto* ui = new G4UIExecutive(argc,argv);

    auto* UImanager = G4UImanager::GetUIpointer();

   if (ui)
{
    ui->SessionStart();
}

    delete ui;
    delete visManager;
    delete runManager;

    return 0;
}