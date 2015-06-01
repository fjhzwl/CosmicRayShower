#include "cosmicsEventGenerator.hh"

#include "G4PhysicalConstants.hh"
#include "G4Event.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SPSAngDistribution.hh"
#include "G4SPSEneDistribution.hh"
#include "G4SPSPosDistribution.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4ThreeVector.hh"
#include "G4SystemOfUnits.hh"

cosmicsEventGenerator::cosmicsEventGenerator()
{
  cosmicsGun = new G4GeneralParticleSource();
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* muonPlus = particleTable->FindParticle(particleName="mu+");
  //G4ParticleDefinition* muonMinus = particleTable->FindParticle(particleName="mu-");
  G4SPSEneDistribution *eneDist = cosmicsGun->GetCurrentSource()->GetEneDist();
  eneDist->SetEnergyDisType("Gauss");
  eneDist->SetEmin(2.0*GeV);
  eneDist->SetEmax(6.0*GeV);
  G4SPSPosDistribution *posDist = cosmicsGun->GetCurrentSource()->GetPosDist();
  posDist->SetPosDisType("Plane");
  posDist->SetPosDisShape("Circle");
  posDist->SetRadius(6000.0*m);
  posDist->SetCentreCoords(G4ThreeVector(0.0*m,0.0*m,12000.0*m));
  G4SPSAngDistribution *angDist = cosmicsGun->GetCurrentSource()->GetAngDist();
  angDist->SetMinTheta(0.0*deg);
  angDist->SetMaxTheta(26.565*deg);
}

cosmicsEventGenerator::~cosmicsEventGenerator()
{
  delete cosmicsGun;
}

void cosmicsEventGenerator::GeneratePrimaries(G4Event* anEvent)
{
  cosmicsGun->GeneratePrimaryVertex(anEvent);
}
