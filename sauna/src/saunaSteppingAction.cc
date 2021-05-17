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
/// \file saunaSteppingAction.cc
/// \brief Implementation of the SteppingAction class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "saunaSteppingAction.hh"
#include "saunaRunAction.hh"
#include "saunaEventAction.hh"

#include "G4RunManager.hh"
#include "G4SteppingManager.hh"
#include "G4TrackingManager.hh"
#include "G4VProcess.hh"
#include "G4UnitsTable.hh"

#include "G4Step.hh"
#include "G4Track.hh"

#include "G4ParticleDefinition.hh"
#include "G4VSensitiveDetector.hh"
#include "G4Electron.hh"

#include <G4ReferenceCountedHandle.hh>

#include "g4csv.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

saunaSteppingAction::saunaSteppingAction(saunaEventAction* anEvent)
  :G4UserSteppingAction(), fEventAction(anEvent)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

saunaSteppingAction::~saunaSteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void saunaSteppingAction::UserSteppingAction(const G4Step* aStep)
{
  G4double eDep_step = aStep->GetTotalEnergyDeposit();
  G4int parentID = aStep->GetTrack()->GetParentID ();
  G4String particle_name = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();

  if (eDep_step > 0.)
  {
    // When gamma i the mother particel the trackID is always == 2
    // And when the electron is the mother particle the track ID == 1
    G4int trackID = aStep->GetTrack()->GetTrackID();

    // G4String detector_name = aStep->GetPostStepPoint()->GetPhysicalVolume()->GetName();
    G4String detector_name = aStep->GetTrack()->GetVolume()->GetName();

    if (detector_name == "Shape1")
    {
      fEventAction->Add_eDep_NaI(eDep_step, trackID, parentID, particle_name);
    }
    if (detector_name == "Shape2")
    {
      fEventAction->Add_eDep_Beta(eDep_step, trackID, parentID, particle_name);
    }

    // G4cout
    // << "\n--------- SteppingAction  ------------"
    // << "\n The trackID: " << trackID 
    // << "\n with the energy deposit: " << eDep_step
    // << "\n and the detector is: " << detector_name
    // << "\n particle name: " << particle_name
    // << "\n---------------------------------------------------------" << G4endl;

  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

