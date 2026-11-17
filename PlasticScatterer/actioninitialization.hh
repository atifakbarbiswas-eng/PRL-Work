#ifndef ACTIONINITIALIZATION_HH
#define ACTIONINITIALIZATION_HH

#include "G4VUserActionInitialization.hh"

class actioninitialization : public G4VUserActionInitialization
{
public:

    actioninitialization();
    virtual ~actioninitialization();

    virtual void Build() const;
};

#endif