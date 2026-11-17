#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4SteppingVerbose.hh"
#include "Randomize.hh"

#include <ctime>

int main(int argc, char** argv)
{
  // Seed the RNG from system time so successive runs differ unless a
  // /random/setSeeds command is given in a macro.
  G4Random::setTheEngine(new CLHEP::RanecuEngine());
  G4long seed = static_cast<G4long>(std::time(nullptr));
  G4Random::setTheSeed(seed);

  // Detect interactive vs batch mode: no extra args -> open the UI;
  // one arg -> treat it as a macro file to execute and exit.
  G4UIExecutive* ui = nullptr;
  if (argc == 1)
  {
    ui = new G4UIExecutive(argc, argv);
  }

  // Construct the run manager. G4RunManagerFactory picks MT if Geant4
  // was built with multithreading support, serial otherwise.
  auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  // Mandatory user initialization classes
  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new PhysicsList());
  runManager->SetUserInitialization(new ActionInitialization());

  // Visualization manager
  G4VisManager* visManager = new G4VisExecutive();
  visManager->Initialize();

  // UI manager, used both for batch macro execution and interactive mode
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (!ui)
  {
    // Batch mode: argv[1] is a macro file, e.g. ./scatPolSim run1.mac
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  }
  else
  {
    // Interactive mode: load the default visualization macro, then
    // hand control to the Geant4 UI session so /gps, /scatPol,
    // /vis, /run etc. commands can be typed directly.
    UImanager->ApplyCommand("/control/execute vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  delete visManager;
  delete runManager;

  return 0;
}
