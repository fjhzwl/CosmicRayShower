#include "cosmicsPhysicsList.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"
#include "G4ProcessManager.hh"
#include "G4ProcessVector.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"
#include "G4MuMultipleScattering.hh"

cosmicsPhysicsList::cosmicsPhysicsList()
{;}

cosmicsPhysicsList::~cosmicsPhysicsList()
{;}

/*void cosmicsPhysicsList::ConstructEM()
{
  theParticleIterator->reset();
  while ( (*theParticleIterator) () ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle-> GetProcessManager();
    G4String particleName = particle->GetParticleName();
    if (particleName == "mu+") {
      pmanager->AddProcess(new G4MuMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4MuIonisation, -1, 2, 2);
      pmanager->AddProcess(new G4MuBremsstrahlung, -1, 3, 3);
      pmanager->AddProcess(new G4MuPairProduction, -1, 4, 4);
    }
  }
}*/

void cosmicsPhysicsList::ConstructLeptons()
{
  G4MuonPlus::MuonPlusDefinition();
  //G4MuonMinus::MuonMinusDefinition();
}


void cosmicsPhysicsList::ConstructParticle()
{
  //particles go here

  ConstructLeptons();

}

void cosmicsPhysicsList::ConstructProcess()
{
  AddTransportation();
 // ConstructEM();
}





void cosmicsPhysicsList::SetCuts()
{
  //Do SetCuts() stuff here
  SetCutsWithDefault();
}
