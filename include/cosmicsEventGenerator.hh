#ifndef cosmicsEventGenerator_h
#define cosmicsEventGenerator_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"

class G4GeneralParticleSource;
class G4Event;

class cosmicsEventGenerator : public G4VUserPrimaryGeneratorAction
{
public:

  cosmicsEventGenerator();
  ~cosmicsEventGenerator();

public:

  void GeneratePrimaries(G4Event* anEvent);
  G4GeneralParticleSource* GetParticleGun(){return cosmicsGun;}

private:

  G4GeneralParticleSource* cosmicsGun;

};

#endif
