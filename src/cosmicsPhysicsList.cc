#include "cosmicsPhysicsList.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"

cosmicsPhysicsList::cosmicsPhysicsList()
{;}

cosmicsPhysicsList::~cosmicsPhysicsList()
{;}

void cosmicsPhysicsList::ConstructParticle()
{
  //particles go here

  ConstructLeptons();

}

void cosmicsPhysicsLIst::ConstructLeptons()
{
  G4MuonPlus::MuonPlusDefinition();
  //G4MuonMinus::MuonMinusDefinition();
}

void cosmicsPhysicsList::ConstructProcess()
{
  AddTransportation();
  ConstructEM();
}

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4Ionisation.hh"
#include "G4MultipleScattering.hh"

void cosmicsPhysicsList::ConstructEM()
{
  theParticleIterator->reset();
  while ( (*theParticleIterator) () ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle-> GetProcessManager();
    G4String paricleName = particle->GetParticleName();
    if (particleName == "mu+") {
      pmanager->AddProcess(new G4MultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4MuIonisation, -1, 2, 2);
      pmanager->AddProcess(new G4MuBremsstrahlung, -1, 3, 3);
      pmanager->AddProcess(new G4MuPairProduction, -1, 4, 4);
    }
  }
}

void cosmicsPhysicsList::SetCuts()
{
  //Do SetCuts() stuff here
  SetCutsWithDefault();
}
