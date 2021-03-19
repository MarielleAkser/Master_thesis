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

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4THitsMap.hh"

#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

#include "g4csv.hh"

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
  // G4SDManager* SDM = G4SDManager::GetSDMpointer();

  // Retrieve the collectionID corresponding to hits in the NaI
  // The variable fShape1Id is initialized to -1 in EventAction.hh) 
  //so this block of code is executed only at the end of the first event. 
  if ( fShape1Id < 0 ) 
  {
   fShape1Id 
     = G4SDManager::GetSDMpointer()->GetCollectionID("Shape1_det");
  }
  //Hits collections  
  // Get all hits-collections available for this events:
  G4HCofThisEvent* HCE = anEvent->GetHCofThisEvent();
  if(!HCE) return;
               
  //Retrieve the hits-collection in the NaI.
  //This comes from a Geant4 multiscorer of type "G4PSEnergyDeposit", which scores 
  //energy deposit.
  G4THitsMap<G4double>* evtMap = 
    dynamic_cast<G4THitsMap<G4double>*>(HCE->GetHC(fShape1Id));
               
  //Store the total energy in a variable
  G4double totEdep = 0.;

  //Sum all individual energy deposits in this event
  for (auto pair : *(evtMap->GetMap()))
  {
    G4double edep = *(pair.second);  
    //Sum the energy deposited in all crystals, irrespectively of threshold.
    totEdep += edep; 
  }  
 
 if (totEdep>0)
 {
  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  // Fill ntuple
  analysisManager->FillNtupleDColumn(0, totEdep);
  G4cout << "The total energy deposited in this event is: " << totEdep/keV << " keV " << G4endl;
 }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
