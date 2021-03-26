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
/// \file saunaEventAction.cc
/// \brief Implementation of the saunaEventAction class

#include "saunaEventAction.hh"
#include "saunaRunAction.hh"
#include "saunaDetectorConstruction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsMap.hh"

#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

#include "g4csv.hh"
#include "G4GenericAnalysisManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

saunaEventAction::saunaEventAction() :
 G4UserEventAction()
{;} 

saunaEventAction::~saunaEventAction()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void saunaEventAction::BeginOfEventAction(const G4Event*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void saunaEventAction::EndOfEventAction(const G4Event* anEvent)
{   
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Retrieve the collectionID corresponding to hits in the NaI
  // The variable fshape1ID is initialized to -1 in EventAction.hh) 
  //so this block of code is executed only at the end of the first event. 
  if ( fshape1ID == -1 ) 
  {
   fshape1ID 
     = G4SDManager::GetSDMpointer()->GetCollectionID("shape1_det/Edep");
  }

  //Store the total energy in a variable
  G4double totEdep = 0.;
  
  //Hits collections
  G4HCofThisEvent* HCE = anEvent->GetHCofThisEvent();

  if (!HCE)
  {
    return;
  }

  G4THitsMap<G4double>* evtMap = 
    static_cast<G4THitsMap<G4double>*>(HCE->GetHC(fshape1ID));


 std::map<G4int,G4double*>::iterator itr; 
  for (itr = evtMap->GetMap()->begin(); itr != evtMap->GetMap()->end(); itr++) 
  {
    G4double edep = *(itr->second);

    //Sum the energy deposited in all crystals, irrespectively of threshold.
    totEdep += edep;
  }

  if (totEdep > 0)
  {
    analysisManager->FillNtupleDColumn(0, totEdep);
    analysisManager->AddNtupleRow(); 
  }
}  


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
