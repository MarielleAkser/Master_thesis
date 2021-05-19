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
#include "G4SubtractionSolid.hh"
#include "G4VSolid.hh"
#include "G4BooleanSolid.hh"
#include "G4SDManager.hh"

#include "G4MultiFunctionalDetector.hh"

#include "G4VSensitiveDetector.hh"

#include "G4SDParticleWithEnergyFilter.hh"

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
  // Shapes for subtractions
  // ------------------------------------------------------------------
    
  G4double bigBetaCyl_rmin = 0*mm, bigBetaCyl_rmax = 10*mm; //Mått från Tomas
  G4double bigBetaCyl_hz = (70/2)*mm; //Mått från Tomas
  G4double bigBetaCyl_phimin = 0.*deg, bigBetaCyl_phimax = 360.*deg; 

  G4double smallBetaCyl_rmin = 0*mm, smallBetaCyl_rmax = bigBetaCyl_rmax - 1*mm;
  G4double smallBetaCyl_hz = bigBetaCyl_hz - 2.5*mm;
  G4double smallBetaCyl_phimin = 0.*deg, smallBetaCyl_phimax = 360.*deg;

  G4double NaIcyl_rmin =  0.0*cm, NaIcyl_rmax = (10.16/2)*cm;
  G4double NaIcyl_hz = (12.7/2)*cm;
  G4double NaIcyl_phimin = 0.*deg, NaIcyl_phimax = 360.*deg;


  G4VSolid* bigBetaCyl = 
    new G4Tubs("BigBetaCyl", 
    bigBetaCyl_rmin, bigBetaCyl_rmax, bigBetaCyl_hz, bigBetaCyl_phimin, bigBetaCyl_phimax); 

  G4VSolid* smallBetaCyl = 
    new G4Tubs("SmallBetaCyl", 
    smallBetaCyl_rmin, smallBetaCyl_rmax, smallBetaCyl_hz, smallBetaCyl_phimin, smallBetaCyl_phimax);

  G4VSolid* NaIcyl = 
    new G4Tubs("NaIcyl", 
    NaIcyl_rmin, NaIcyl_rmax, NaIcyl_hz, NaIcyl_phimin, NaIcyl_phimax);


  // ------------------------------------------------------------------
  // shape1 = NaI detector
  // ------------------------------------------------------------------
  
  G4Material* shape1_mat = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  G4ThreeVector pos1 = G4ThreeVector(0., 0., 0.);

  G4RotationMatrix* rm = new G4RotationMatrix();
  rm->rotateX(90.*deg);

  // Getting the volume of the NaI. It is a hole for the beta-cell 
  // so that volume is subtracted
  G4VSolid* solidShape1 = new G4SubtractionSolid("Shape1", NaIcyl, bigBetaCyl, rm, pos1);
  

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
  // Shape 2 = beta detector 
  // ------------------------------------------------------------------
  
  // The material and position
  G4double density = 1.032*g/cm3;

  G4Material* hydrogen = nist->FindOrBuildMaterial("G4_H");
  G4Material* carbone = nist->FindOrBuildMaterial("G4_C");

  G4Material* shape2_mat = new G4Material("BC404",density, 2);
  shape2_mat->AddMaterial(hydrogen, 8.4*perCent);
  shape2_mat->AddMaterial(carbone, 91.6*perCent);

  G4ThreeVector pos2 = G4ThreeVector(0., 0., (NaIcyl_rmin)); 

  // Getting the volume of the Beta-cell by subtracting the two 
  // beta cylinders define above
  G4VSolid* solidShape2 = new G4SubtractionSolid("Shape2", bigBetaCyl, smallBetaCyl, 0, pos2);
  
  G4LogicalVolume* logicShape2 =                         
    new G4LogicalVolume(solidShape2,         //its solid
                        shape2_mat,          //its material
                        "Shape2");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "Shape2",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  

  // ------------------------------------------------------------------
  // Aluminum layer covering Beta cell
  // ------------------------------------------------------------------

  G4Material* AlLayer_mat = nist->FindOrBuildMaterial("G4_Al");

  G4double AlLayer_rmin = bigBetaCyl_rmax, AlLayer_rmax = AlLayer_rmin + 0.2*mm;
  G4double AlLayer_hz = bigBetaCyl_hz;
  G4double AlLayer_phimin = 0.*deg, AlLayer_phimax = 360.*deg; 

  G4Tubs* solidAlLayer =    
    new G4Tubs("AlLayer", 
    AlLayer_rmin, AlLayer_rmax, AlLayer_hz, AlLayer_phimin, AlLayer_phimax);

  G4LogicalVolume* logicAlLayer =                         
    new G4LogicalVolume(solidAlLayer,         //its solid
                        AlLayer_mat,          //its material
                        "AlLayer");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    pos2,                    //at position
                    logicAlLayer,             //its logical volume
                    "AlLayer",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  
  // ------------------------------------------------------------------
  // Lead-shield 
  // ------------------------------------------------------------------
 
  G4Material* LeadMat = nist->FindOrBuildMaterial("G4_Pb");
  
  G4double ShieldLead_rmin =  NaIcyl_rmax, ShieldLead_rmax = (ShieldLead_rmin + 5*cm);
  G4double ShieldLead_hz = NaIcyl_hz;
  G4double ShieldLead_phimin = 0.*deg, ShieldLead_phimax = 360.*deg;
  
  G4Tubs* solidShieldLead =    
    new G4Tubs("ShieldLead", 
    ShieldLead_rmin, ShieldLead_rmax, ShieldLead_hz, ShieldLead_phimin, ShieldLead_phimax);

  G4LogicalVolume* logicShieldLead =                         
    new G4LogicalVolume(solidShieldLead,         //its solid
                        LeadMat,          //its material
                        "ShieldLead");           //its name


  new G4PVPlacement(rotationMatrix,          //rotation 90deg in x
                    pos1,                    //at position
                    logicShieldLead,             //its logical volume
                    "ShieldLead",                //its name
                    logicWorld,                //its mother volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  // Top and bottom Lead Shield
  G4double ShieldLeadPuck_rmin = 0, ShieldLeadPuck_rmax = ShieldLead_rmax;
  G4double ShieldLeadPuck_hz = 5/2*cm;
  G4double ShieldLeadPuck_phimin = 0.*deg, ShieldLeadPuck_phimax = 360.*deg;

  G4ThreeVector posLeadPuck = G4ThreeVector(0., NaIcyl_hz + ShieldLeadPuck_hz, 0.);

  G4Tubs* solidShieldLeadPuck =    
    new G4Tubs("ShieldLeadPuck", 
    ShieldLeadPuck_rmin, ShieldLeadPuck_rmax, ShieldLeadPuck_hz, ShieldLeadPuck_phimin, ShieldLeadPuck_phimax);

  G4LogicalVolume* logicShieldLeadPuck =                         
    new G4LogicalVolume(solidShieldLeadPuck,         //its solid
                        LeadMat,                  //its material
                        "ShieldLeadPuck");           //its name

  new G4PVPlacement(rotationMatrix,          //rotation 90deg in x
                    posLeadPuck,                    //at position
                    logicShieldLeadPuck,             //its logical volume
                    "ShieldLead",                //its name
                    logicWorld,                //its mother volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  

  new G4PVPlacement(rotationMatrix,          //rotation 90deg in x
                    -posLeadPuck,                    //at position
                    logicShieldLeadPuck,             //its logical volume
                    "ShieldLead",                //its name
                    logicWorld,                //its mother volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  


  // ------------------------------------------------------------------
  // PM-tube1
  // ------------------------------------------------------------------
  
  G4Material* PM_Mat = nist->FindOrBuildMaterial("G4_Al");

  G4double PM_rmin = 0.0*mm, PM_rmax = bigBetaCyl_rmax;
  G4double PM_hz = 5*cm;
  G4double PM_phimin = 0.*deg, PM_phimax = 360.*deg;

  G4ThreeVector posPM = G4ThreeVector(0., 0., bigBetaCyl_hz + PM_hz);

  // Cylinder shape 
  G4Tubs* solidPM1 =    
    new G4Tubs("PM1", 
    PM_rmin, PM_rmax, PM_hz, PM_phimin, PM_phimax);
  
  G4LogicalVolume* logicPM1 =                         
    new G4LogicalVolume(solidPM1,         //its solid
                        PM_Mat,          //its material 
                        "PM1");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    posPM,                //at position
                    logicPM1,             //its logical volume
                    "PM1",                //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
                     
// ------------------------------------------------------------------
// PM-tube2
// ------------------------------------------------------------------

  G4Tubs* solidPM2 =    
    new G4Tubs("PM2", 
    PM_rmin, PM_rmax, PM_hz, PM_phimin, PM_phimax);   // Same size as PM1
  
  G4LogicalVolume* logicPM2 =                         
    new G4LogicalVolume(solidPM2,         //its solid
                        PM_Mat,          //its material 
                        "PM2");           //its name
               
  new G4PVPlacement(0,                       //no rotation
                    -posPM,                //at position
                    logicPM2,             //its logical volume
                    "PM2",                //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


  
  //always return the physical World
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void saunaDetectorConstruction::ConstructSDandField()
 {
   G4SDManager::GetSDMpointer()->SetVerboseLevel(1);

  // Shape1 - NaI detector becomes a MultiFunctionalDetector
  G4MultiFunctionalDetector* scorerShape1 = 
    new G4MultiFunctionalDetector("shape1_det");
  G4SDManager::GetSDMpointer()->AddNewDetector(scorerShape1);

  G4VPrimitiveScorer* primitiv1 = new G4PSEnergyDeposit("Edep_NaI");


  // Shape2 - Beta-detector becomes a MultiFunctionalDetector
  G4MultiFunctionalDetector* scorerShape2 = 
    new G4MultiFunctionalDetector("shape2_det");
  G4SDManager::GetSDMpointer()->AddNewDetector(scorerShape2);

  G4VPrimitiveScorer* primitiv2 = new G4PSEnergyDeposit("Edep_Beta");
  
  scorerShape1->RegisterPrimitive(primitiv1);
  scorerShape2->RegisterPrimitive(primitiv2);

  SetSensitiveDetector("Shape1",scorerShape1);
  SetSensitiveDetector("Shape2",scorerShape2);

 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
