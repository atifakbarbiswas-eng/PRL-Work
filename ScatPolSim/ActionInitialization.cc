#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization()
: G4VUserActionInitialization()
{}

ActionInitialization::~ActionInitialization() {}

void ActionInitialization::BuildForMaster() const
{
  // Master thread (multi-threaded mode): only RunAction is needed here,
  // since event-level actions run on worker threads. RunAction's
  // histogram/ntuple booking still needs to happen on master for
  // merging in MT mode.
  SetUserAction(new RunAction());
}

void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction());
  SetUserAction(new RunAction());

  auto eventAction = new EventAction();
  SetUserAction(eventAction);

  SetUserAction(new SteppingAction(eventAction));
}
