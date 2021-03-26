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
//
/// \file saunaDetectorConstruction.cc
/// \brief Implementation of the saunaDetectorConstruction class

#include "saunaDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4SDChargedFilter.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"


#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4SDManager.hh"

#include "G4MultiFunctionalDetector.hh"

#include "G4VSensitiveDetector.hh"

#include "G4SDParticleWithEnergyFilter.hh"

// #include "G4VPrimitiveSensitivity.hh"

#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSTrackLength.hh"
#include "G4Colour.hh"

#include "G4PSDoseDeposit.hh"
#include "G4VisAttributes.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

saunaDetectorConstruction::saunaDetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

saunaDetectorConstruction::~saunaDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* saunaDetectorConstruction::Construct()
{  

  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  G4bool checkOverlaps = true;

  
  // ------------------------------------------------------------------    
  // World
  // ------------------------------------------------------------------
  
  G4double worldSizeX = 1 * m;
  G4double worldSizeY = 1 * m;
  G4double worldSizeZ = 1 * m;
  
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.25*worldSizeX, 0.25*worldSizeY, 0.25*worldSizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     

  // ------------------------------------------------------------------
  // shape1 = NaI(Tl) detector
  // ------------------------------------------------------------------
  
  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  G4ThreeVector pos1 = G4ThreeVector(0., 0., 0.);
        
  // Cylinder section shape       
  G4double shape1_rmin =  5.07*cm, shape1_rmax = 5.08*cm;
  G4double shape1_hz = (12.7/2)*cm;
  G4double shape1_phimin = 0.*deg, shape1_phimax = 360.*deg;
  
  G4Tubs* solidShape1 =    
    new G4Tubs("Shape1", 
    shape1_rmin, shape1_rmax, shape1_hz, shape1_phimin, shape1_phimax);

  G4LogicalVolume* logicShape1 =                         
    new G4LogicalVolume(solidShape1,         //its solid
                        shape1_mat,          //its material
                        "Shape1");           //its name


  G4RotationMatrix* rotationMatrix = new G4RotationMatrix();
  rotationMatrix->rotateX(90.*deg);

  new G4PVPlacement(rotationMatrix,          //rotation 90deg in x
                    pos1,                    //at position
                    logicShape1,             //its logical volume
                    "Shape1",                //its name
                    logicWorld,                //its mother volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


  // ------------------------------------------------------------------
  // Lead-shield 
  // ------------------------------------------------------------------
 
  // G4Material* LeadMat = nist->FindOrBuildMaterial("G4_Pb");
        
  // // Cylinder section shape       
  // G4double ShieldLead_rmin =  5.08*cm, ShieldLead_rmax = 10.08*cm;
  // G4double ShieldLead_hz = (12.7/2)*cm;
  // G4double ShieldLead_phimin = 0.*deg, ShieldLead_phimax = 360.*deg;
  
  // G4Tubs* solidShieldLead =    
  //   new G4Tubs("ShieldLead", 
  //   ShieldLead_rmin, ShieldLead_rmax, ShieldLead_hz, ShieldLead_phimin, ShieldLead_phimax);

  // G4LogicalVolume* logicShieldLead =                         
  //   new G4LogicalVolume(solidShieldLead,         //its solid
  //                       LeadMat,          //its material
  //                       "ShieldLead");           //its name


  // new G4PVPlacement(rotationMatrix,          //rotation 90deg in x
  //                   pos1,                    //at position
  //                   logicShieldLead,             //its logical volume
  //                   "ShieldLead",                //its name
  //                   logicWorld,                //its mother volume
  //                   false,                   //no boolean operation
  //                   0,                       //copy number
  //                   checkOverlaps);          //overlaps checking

  // ------------------------------------------------------------------
  // Shape 2 = beta detector (one side of NaI)
  // ------------------------------------------------------------------
  
  // Cylinder shape       
  // G4double shape2_rmin = 6.35*mm, shape2_rmax = (35/2)*mm;
  // G4double shape2_hz = (50.8/2)*mm;
  // G4double shape2_phimin = 0.*deg, shape2_phimax = 360.*deg;     
  
  // G4Tubs* solidShape2 =    
  //   new G4Tubs("Shape2", 
  //   shape2_rmin, shape2_rmax, shape2_hz, shape2_phimin, shape2_phimax);

  // // The material and position
  // G4Material* shape2_mat = nist->FindOrBuildMaterial("G4_BONE_COMPACT_ICRU");
  // G4ThreeVector pos2 = G4ThreeVector(0., 0., (shape1_rmin)); 

  
  // G4LogicalVolume* logicShape2 =                         
  //   new G4LogicalVolume(solidShape2,         //its solid
  //                       shape2_mat,          //its material
  //                       "Shape2");           //its name
               
  // new G4PVPlacement(0,                       //no rotation
  //                   pos2,                    //at position
  //                   logicShape2,             //its logical volume
  //                   "Shape2",                //its name
  //                   logicWorld,                //its mother  volume
  //                   false,                   //no boolean operation
  //                   0,                       //copy number
  //                   checkOverlaps);          //overlaps checking
  
  
  
  // ------------------------------------------------------------------
  // Shape 3 = beta detector (the other side of NaI)
  // ------------------------------------------------------------------
  
  // Cylinder shape, with the same dimentions as shape2    
  // G4Tubs* solidShape3 =    
  //   new G4Tubs("Shape3", 
  //   shape2_rmin, shape2_rmax, shape2_hz, shape2_phimin, shape2_phimax);
  
  // G4LogicalVolume* logicShape3 =                         
  //   new G4LogicalVolume(solidShape3,         //its solid
  //                       shape2_mat,          //its material (same as shape 2)
  //                       "Shape3");           //its name
               
  // new G4PVPlacement(0,                       //no rotation
  //                   -pos2,                   //at position
  //                   logicShape3,             //its logical volume
  //                   "Shape3",                //its name
  //                   logicWorld,              //its mother  volume
  //                   false,                   //no boolean operation
  //                   0,                       //copy number
  //                   checkOverlaps);          //overlaps checking
                     
  // // Set Shape2 and 3 as scoring volume
  // //
  // fScoringVolume = logicShape2;
  // fScoringVolume = logicShape3;
  //
  //always return the physical World
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void saunaDetectorConstruction::ConstructSDandField()
 {
   G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  G4MultiFunctionalDetector* scorerShape1 = new G4MultiFunctionalDetector("shape1_det");
  G4SDManager::GetSDMpointer()->AddNewDetector(scorerShape1);

  G4VPrimitiveScorer* primitiv1 = new G4PSEnergyDeposit("Edep");

  // Filter to only read gamma-rays:
  // G4SDParticleFilter* filter =
  //   new G4SDParticleFilter("gammaFilter");
  // filter->add("gamma");

  // primitiv1->SetFilter(filter);
  
  scorerShape1->RegisterPrimitive(primitiv1);

  SetSensitiveDetector("Shape1",scorerShape1);

 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
