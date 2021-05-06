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

#include "saunaTrackingAction.hh"
#include "saunaSteppingAction.hh"

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

#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4DynamicParticle.hh"
#include "G4Step.hh"

#include "G4PrimaryVertex.hh"
#include "G4ParticleDefinition.hh"

#include "G4AttDef.hh"
#include "G4VHit.hh"
#include "G4VHitsCollection.hh"

#include "G4Trajectory.hh"
#include "G4TrajectoryContainer.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

saunaEventAction::saunaEventAction() :
 G4UserEventAction(), fTotalEnergyDeposit_Beta(0.), fTotalEnergyDeposit_NaI(0.)
{;} 

saunaEventAction::~saunaEventAction()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void saunaEventAction::BeginOfEventAction(const G4Event* )
{
  fTotalEnergyDeposit_electron = 0.; 
  fTotalEnergyDeposit_gamma = 0.;

  fTotalEnergyDeposit_NaI = 0.;
  fTotalEnergyDeposit_Beta = 0.;

  // G4cout
  // << "\n //////////////// Begin Of EventAction ////////////// \n"
  // << G4endl;

  // G4int nr_primary_vertex = anEvent->GetNumberOfPrimaryVertex();
  // for (int i=0; i<nr_primary_vertex; i++)
  // {
  //   G4cout
  //   << "\n track ID : " << anEvent->GetPrimaryVertex(0)->GetPrimary(0)->GetTrackID ()
  //   << G4endl;
  // }
  // G4cout
  // << "\n //////////////// /////////////////// ////////////// \n"
  // << G4endl;

  // Retrieve the collectionID corresponding to hits in the NaI
  // The variable fshape1ID is initialized to -1 in EventAction.hh) 
  //so this block of code is executed only at the end of the first event. 
  if ( fshape1ID == -1 ) 
  {
   fshape1ID 
     = G4SDManager::GetSDMpointer()->GetCollectionID("shape1_det/Edep_NaI");
  }
  if ( fshape2ID == -1 ) 
  {
   fshape2ID 
     = G4SDManager::GetSDMpointer()->GetCollectionID("shape2_det/Edep_Beta");
  }



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void saunaEventAction::EndOfEventAction(const G4Event* )
{   
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // // Retrieve the collectionID corresponding to hits in the NaI
  // // The variable fshape1ID is initialized to -1 in EventAction.hh) 
  // //so this block of code is executed only at the end of the first event. 
  // if ( fshape1ID == -1 ) 
  // {
  //  fshape1ID 
  //    = G4SDManager::GetSDMpointer()->GetCollectionID("shape1_det/Edep_NaI");
  // }

  // if ( fshape2ID == -1 ) 
  // {
  //  fshape2ID 
  //    = G4SDManager::GetSDMpointer()->GetCollectionID("shape2_det/Edep_Beta");
  // }

  G4cout
  << "\n ---------------------EndOfEvent---------------------- \n"
   << " The energy deposit in NaI: " << fTotalEnergyDeposit_NaI
  << " \n and the energy deposit in Beta: " << fTotalEnergyDeposit_Beta
  << "\n and the parent name in beta: " << fParentName_Beta
  << "\n ----------------------------------------------------- \n"
  << G4endl;

  // Filling the files
  analysisManager->FillNtupleDColumn(1, fTotalEnergyDeposit_NaI);
  analysisManager->FillNtupleDColumn(3, fTotalEnergyDeposit_Beta);
  analysisManager->AddNtupleRow(); 


}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


  //Store the total energy in a variable
//   G4double totEdep_NaI = 0.;
//   G4double totEdep_Beta = 0.;
  
//   //Hits collections
//   G4HCofThisEvent* HCE = anEvent->GetHCofThisEvent();

//   if (!HCE)
//   {
//     return;
//   }

//   G4THitsMap<G4double>* evtMap_NaI = 
//     static_cast<G4THitsMap<G4double>*>(HCE->GetHC(fshape1ID));

//   G4THitsMap<G4double>* evtMap_Beta = 
//     static_cast<G4THitsMap<G4double>*>(HCE->GetHC(fshape2ID));

//  std::map<G4int,G4double*>::iterator itr; 

//   for (itr = evtMap_NaI->GetMap()->begin(); itr != evtMap_NaI->GetMap()->end(); itr++) 
//   {
//     G4double edep_NaI = *(itr->second);

//     //Sum the energy deposited
//     totEdep_NaI += edep_NaI;
    
//   // Getting the name of the mother particle 
//   // bool flag = true;
//   //   if (flag)
//   //   {
//   //     G4String parent_name;
//   //     auto trajectory_vector_ptr = anEvent->GetTrajectoryContainer()->GetVector();
//   //     if( 0 !=  trajectory_vector_ptr)
//   //     {
//   //       for( auto trajectory : *(trajectory_vector_ptr ))
//   //       {
//   //           // if( 0 == trajectory->GetParentID() )
//   //           // {
//   //               // TODO: Might need more "criteria" (besides the name)
//   //               // to deduce which of the particles it was, in a tripple-
//   //               // particle source. Perhaps trajectory->GetInitialMomentum() ?
//   //               parent_name = trajectory->GetParticleName();
//   //               G4cout
//   //               << "\n----------------------NaI-----------------------------" 
//   //               << " \n parent name: " << parent_name << " \n " 
//   //               // << anEvent->GetHCofThisEvent()->GetHC() << " \n "
//   //               << "\n----------------------NaI-----------------------------" 
//   //               << G4endl;
//   //           // }
//   //       }
//   //     }
//   //     if( 1 > parent_name.size() )
//   //     {
//   //       throw std::logic_error("Could not find name of mother particle?");
//   //     }
//   //     flag = false;
//   //     // analysisManager->FillNtupleSColumn(0, parent_name);
//   //   }
//   }

//   // evtMap_NaI->PrintAllHits();
//   // auto def = evtMap_NaI->GetSize();
//   //   G4cout
//   //   << "\n NaI Map: \n"
//   //   << def
//   //   << "\n" << G4endl;
  
//   for (itr = evtMap_Beta->GetMap()->begin(); itr != evtMap_Beta->GetMap()->end(); itr++) 
//   {
//     G4double edep_Beta = *(itr->second);
//     //Sum the energy deposited
//     totEdep_Beta += edep_Beta;

//     // analysisManager->FillNtupleSColumn(2, parent_name);
//   }
//   // evtMap_Beta->PrintAllHits();
//   // G4int nr = anEvent->GetNumberOfPrimaryVertex();
//   //     G4cout
//   //     << "\n---------------------------------------------------" 
//   //     << " \n nr of primary vertex: " << nr << " \n " << G4endl;
//   // for (int i=0; i<nr; i++)
//   // {
//   //   G4String namn = anEvent->GetPrimaryVertex(i)->GetPrimary(0)->GetParticleDefinition()->GetParticleName();
//   //   G4String track_ID = anEvent->GetPrimaryVertex(i)->GetPrimary(0)->GetTrackID();
//   //   G4cout
//   //     << "\n name of particle: " << namn 
//   //     << "\n with track ID of particle: " << track_ID 
//   //     << "\n---------------------------------------------------" << G4endl;
//   // }

//   // // G4int cont = anEvent->GetTrajectoryContainer();

//   // G4cout
//   // << "\n-------------------container: " << anEvent->GetTrajectoryContainer() << "------------------ \n"
//   // << G4endl;

//   // G4int size_cont = anEvent->GetTrajectoryContainer()->size();
//   // for (int i=0; i<size_cont; i++)
//   // {
//   // G4cout
//   // << anEvent->GetTrajectoryContainer()->operator[](i)->GetParticleName()
//   // << "\n-------------------------------------------------- \n" << G4endl;
//   // }

  



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
