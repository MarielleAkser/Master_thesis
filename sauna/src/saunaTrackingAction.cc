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
/// \file saunaTrackingAction.cc
/// \brief Implementation of the TrackingAction class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "saunaTrackingAction.hh"
#include "saunaRunAction.hh"
#include "saunaEventAction.hh"

#include "G4RunManager.hh"
#include "G4TrackingManager.hh"
#include "G4VProcess.hh"
#include "G4UnitsTable.hh"

#include "G4Track.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"

#include "G4ParticleDefinition.hh"

#include "g4csv.hh"

#include "G4VTouchable.hh"
#include "G4Electron.hh"
#include "G4TrackStatus.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

saunaTrackingAction::saunaTrackingAction(saunaEventAction* anEvent)
  :G4UserTrackingAction(), fEventAction(anEvent)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

saunaTrackingAction::~saunaTrackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void saunaTrackingAction::PreUserTrackingAction(const G4Track* )
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void saunaTrackingAction::PostUserTrackingAction(const G4Track* )
{
  // G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // G4int particle_ID = aTrack->GetParentID();
  // G4String particle_name = aTrack->GetParticleDefinition()->GetParticleName();
  // G4double energy_deposit = aTrack->GetStep()->GetTotalEnergyDeposit();
  
  // G4String eDep_volume = aTrack->GetVolume()->GetName();

  // G4double first_E_kin = aTrack->GetStep()->GetPreStepPoint()->GetKineticEnergy();
  // G4double last_E_kin = aTrack->GetKineticEnergy();

  // G4cout
  // << "\n--------------------PostTrackingAction-----------------------"
  // << "\n The Energy deposit is: " << energy_deposit
  // << "\n In volume: " << eDep_volume
  // << "\n And the particle name is: " << particle_name
  // // << "\n First kinetic energy: " << first_E_kin
  // // << "\n Last kinetic energy: " << last_E_kin
  // << "\n ------------------------------------------------------------ \n" << G4endl;


  // G4TrackVector* secTracks = fpTrackingManager -> GimmeSecondaries();
  // size_t nrSecTracks = 0;

  // if(secTracks) 
  // { 
  //    nrSecTracks = (*secTracks).size();       

  //    for(size_t i = 0; i < nrSecTracks; i++) { 
  //       if((*secTracks)[i] -> GetDefinition() == G4Electron::Definition()) 
  //             counter++;
  //    }
  // }


  // if (energy_deposit > 0)
  // {
  //   if (particle_ID == 0)
  //   {
  //     if (eDep_volume == "Shape1")
  //     {
  //       analysisManager->FillNtupleSColumn(0, particle_name);
  //     }

  //     if (eDep_volume == "Shape2")
  //     {
  //       analysisManager->FillNtupleSColumn(2, particle_name);
  //     }

  //     G4cout
  //     << "\n--------------------PostTrackingAction-----------------------"
  //     << "\n eDep in volume: " << eDep_volume
  //     << "\n with particle ID: " <<  particle_ID
  //     << "\n The particle name is: " << particle_name
  //     << "\n---------------------------------------------------------" << G4endl;

  //   }
  // }
  
  // G4TrackVector* secTracks = fpTrackingManager -> GimmeSecondaries();
  // size_t nrSecTracks;


  // G4cout
  //     << "\n--------------------PostTrackingAction-----------------------"
  //     << "\n eDep in volume: " << eDep_volume
  //     << "\n The particle name is: " << particle_name
  //     << "\n secondaries: " << nrSecTracks
  //     << "\n---------------------------------------------------------" << G4endl;


}
