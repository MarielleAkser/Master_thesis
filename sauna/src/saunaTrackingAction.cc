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

void saunaTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
  G4int parent_ID = aTrack->GetParentID();

  G4String detector_name = aTrack->GetStep()->GetPreStepPoint()->GetPhysicalVolume()->GetName();

  G4String particle_name = aTrack->GetParticleDefinition()->GetParticleName();

  G4int track_id = aTrack->GetTrackID();

  G4TrackVector* secTracks = fpTrackingManager -> GimmeSecondaries();
  G4int nrSecTracks = (*secTracks).size();

  G4cout
      << "\n--------------------PostTrackingAction-----------------------"
      << "\n eDep in volume: " << detector_name
      << "\n with parent ID: " <<  parent_ID
      << "\n and name: " << particle_name
      << "\n Track ID: " << track_id
      << "\n nr of secondary tracks: " << nrSecTracks
      << "\n---------------------------------------------------------" 
    << G4endl;

}
