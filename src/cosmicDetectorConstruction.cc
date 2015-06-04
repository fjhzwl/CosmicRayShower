//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id$
//
/// \file cosmicDetectorConstruction.cc
/// \brief Implementation of the cosmicDetectorConstruction class

#include "cosmicDetectorConstruction.hh"
#include "cosmicSteppingAction.hh"
   // use of stepping action to set the accounting volume

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4GDMLParser.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

cosmicDetectorConstruction::cosmicDetectorConstruction()
: G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

cosmicDetectorConstruction::~cosmicDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* cosmicDetectorConstruction::Construct()
{  
   /* 
    G4GDMLParser *cosmicGDMLParser = new G4GDMLParser();
    cosmicGDMLParser->Clear();
    cosmicGDMLParser->SetOverlapCheck(false); 
    cosmicGDMLParser->Read("auxiliary.gdml");
    fPhysWorld = cosmicGDMLParser->GetWorldVolume();
    G4LogicalVolume *logWorld = fPhysWorld->GetLogicalVolume();*/

 // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  //Geometry Parameters
  
  G4double earthRadius = 100*cm;
  G4double tropMax = 11*cm;
  G4double stratMax = 55*cm;
  G4double detHeight = 20*cm;
  G4double detRad = 2*detHeight;

  // Envelope parameters
  //
  G4double env_sizeXY = 2.2*earthRadius, env_sizeZ = 2.2*earthRadius;
  G4Material* env_mat = nist->FindOrBuildMaterial("G4_AIR");
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
    fPhysWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Envelope
  //  
  G4Box* solidEnv =    
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 
  //     
  // Shape 1
  //
  
  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_ETHYL_ALCOHOL");
  G4ThreeVector pos1 = G4ThreeVector(0, 0*cm, 0*cm);
  /*      
  // Conical section shape       
  G4double shape1_rmina =  0.*cm, shape1_rmaxa = 2.*cm;
  G4double shape1_rminb =  0.*cm, shape1_rmaxb = 4.*cm;
  G4double shape1_hz = 3.*cm;
  G4double shape1_phimin = 0.*deg, shape1_phimax = 360.*deg;
  G4Cons* solidShape1 =    
    new G4Cons("Shape1", 
    shape1_rmina, shape1_rmaxa, shape1_rminb, shape1_rmaxb, shape1_hz,
    shape1_phimin, shape1_phimax);*/
/*
  // Full sphere shape
  G4double shape1_rmax = 4*cm;
  G4Orb* solidShape1 =    
    new G4Orb("Shape1",                     //its name
              shape1_rmax);                 //its size*/

  // Sphere shape
  G4double shape1_rmin = 0*cm, shape1_rmax = earthRadius;
  G4double shape1_thetamin = 0.*deg, shape1_thetamax =  180.*deg;    
  G4double shape1_phimin = 0.*deg, shape1_phimax =  360.*deg;    
  G4Sphere* solidShape1 =    
    new G4Sphere("Shape1",                  //its name
        shape1_rmin, shape1_rmax,                //its size
        shape1_phimin, shape1_phimax,            //phi angle
        shape1_thetamin, shape1_thetamax);       //theta angle
     
/*  // Box shape
  G4double shape1_dx = 8*cm, shape1_dy = 8*cm, shape1_dz = 8*cm;    
  G4Box* solidShape1 =    
    new G4Box("Shape1",                     //its name
         0.5*shape1_dx, 0.5*shape1_dy, 0.5*shape1_dz);     //its size
*/
                     
 G4LogicalVolume* logicShape1 =                         
    new G4LogicalVolume(solidShape1,         //its solid
                        shape1_mat,          //its material
                        "Shape1");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Shape1",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


  //     
  // Shape 2
  //
/*  G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
  G4ThreeVector pos2 = G4ThreeVector(0, -1*cm, 7*cm);

  //  Shape 2 - conical section shape       
   G4double shape2_rmina =  0.*cm, shape2_rmaxa = 5.*cm;
   G4double shape2_rminb =  0.*cm, shape2_rmaxb = 8.*cm;
   G4double shape2_hz = 3.*cm;
   G4double shape2_phimin = 0.*deg, shape2_phimax = 360.*deg;
   G4Cons* solidShape2 =    
     new G4Cons("Shape2", 
     shape2_rmina, shape2_rmaxa, shape2_rminb, shape2_rmaxb, shape2_hz,
     shape2_phimin, shape2_phimax);
*/
/*
  // Trapezoid shape       
  G4double shape2_dxa = 12*cm, shape2_dxb = 12*cm;
  G4double shape2_dya = 10*cm, shape2_dyb = 16*cm;
  G4double shape2_dz  = 6*cm;      
  G4Trd* solidShape2 =    
    new G4Trd("Shape2",                      //its name
              0.5*shape2_dxa, 0.5*shape2_dxb, 
              0.5*shape2_dya, 0.5*shape2_dyb, 0.5*shape2_dz); //its size
                
  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,         //its solid
                        shape2_mat,          //its material
                        "Shape2");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "Shape2",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  */              
  // Set scoring volume to stepping action 
  // (where we will account energy deposit)
  //


  G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_WATER");
  G4ThreeVector pos2 = G4ThreeVector(0, 0*cm, 0*cm);
  G4double shape2_rmin = earthRadius, shape2_rmax = earthRadius+tropMax;
  G4double shape2_thetamin = 0.*deg, shape2_thetamax =  180.*deg;    
  G4double shape2_phimin = 0.*deg, shape2_phimax =  360.*deg;    
  G4Sphere* solidShape2 =    
    new G4Sphere("Shape2",                  //its name
        shape2_rmin, shape2_rmax,                //its size
        shape2_phimin, shape2_phimax,            //phi angle
        shape2_thetamin, shape2_thetamax);       //theta angle
  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,         //its solid
                        shape2_mat,          //its material
                        "Shape2");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "Shape2",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

   G4Material* shape3_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4ThreeVector pos3 = G4ThreeVector(0, 0*cm, 0*cm);
  G4double shape3_rmin = earthRadius+tropMax, shape3_rmax = earthRadius+stratMax;
  G4double shape3_thetamin = 0.*deg, shape3_thetamax =  180.*deg;    
  G4double shape3_phimin = 0.*deg, shape3_phimax =  360.*deg;    
  G4Sphere* solidShape3 =    
    new G4Sphere("Shape3",                  //its name
        shape3_rmin, shape3_rmax,                //its size
        shape3_phimin, shape3_phimax,            //phi angle
        shape3_thetamin, shape3_thetamax);       //theta angle
  G4LogicalVolume* logicShape3 =                         
    new G4LogicalVolume(solidShape3,         //its solid
                        shape3_mat,          //its material
                        "Shape3");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos3,                    //at position
                    logicShape3,             //its logical volume
                    "Shape3",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

 G4Material* shape4_mat = nist->FindOrBuildMaterial("G4_AIR");
  G4ThreeVector pos4 = G4ThreeVector(0, 0*cm, earthRadius+0.5*detHeight);
  G4double shape4_rmin = 0, shape4_rmax = detRad;
  G4double shape4_thetamin = 0.*deg, shape4_thetamax =  360.*deg;    
  G4double shape4_z = 0.5*detHeight;    
  G4Tubs* solidShape4 =    
    new G4Tubs("Shape4",                  //its name
        shape4_rmin, shape4_rmax, 
        shape4_z,	               //its size
        shape4_thetamin, shape4_thetamax);       //theta angle
  G4LogicalVolume* logicShape4 =                         
    new G4LogicalVolume(solidShape4,         //its solid
                        shape4_mat,          //its material
                        "Shape4");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos4,                    //at position
                    logicShape4,             //its logical volume
                    "Shape4",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


  cosmicSteppingAction* steppingAction = cosmicSteppingAction::Instance(); 
  ////steppingAction->SetVolume(logicShape1);
  steppingAction->SetVolume(logicShape1);


  //
  //always return the physical World
  //
  return fPhysWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
