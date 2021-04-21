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
#include "G4VProcess.hh"
#include "G4UnitsTable.hh"

#include "G4Step.hh"
#include "G4Track.hh"

#include "G4ParticleDefinition.hh"

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
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
   
  // step length of primary particle
  // G4int parent_ID = aStep->GetTrack()->GetParentID();

  //   if (parent_ID == 0)
  //   {
  //     G4cout
  //   << "\n--------------------SteppingAction-----------------------"
  //   << " \n The parentID is: " << parent_ID << " \n " << G4endl;

  //     G4String name_parent = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();

  //     G4cout
  //   << " \n The parent name is: " << name_parent << " \n " << G4endl;

  //   }


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

