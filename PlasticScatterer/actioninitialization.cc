#include "actioninitialization.hh"

#include "particlegun.hh"
#include "runaction.hh"
#include "eventaction.hh"
#include "steppingaction.hh"

actioninitialization::actioninitialization()
{
}

actioninitialization::~actioninitialization()
{
}

void actioninitialization::Build() const
{
    SetUserAction(new particlegun());

    auto run = new runaction();
    SetUserAction(run);

    auto event = new eventaction();
    SetUserAction(event);

   SetUserAction(
    new steppingaction(
        run,
        event,
        run->GetAnalysis()));
}