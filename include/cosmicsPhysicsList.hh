#ifndef cosmicsPhysicsList_h
#define cosmicsPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class cosmicsPhyiscsList: public G4VUserPhysicsList
{
  public:
    cosmicsPhysicsList();
    ~cosmicsPhysicsList();

  protected:
    void ConstructParticle();
    void ConstructProcess();
    void SetCuts();

};

#endif
