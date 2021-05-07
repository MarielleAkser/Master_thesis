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
/// \file saunaActionInitialization.cc
/// \brief Implementation of the saunaActionInitialization class

#include "saunaActionInitialization.hh"
#include "saunaPrimaryGeneratorAction.hh"

#include "saunaEventAction.hh"
#include "saunaRunAction.hh"
#include "saunaTrackingAction.hh"
#include "saunaSteppingAction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//! Class constructor
saunaActionInitialization::saunaActionInitialization()
 : G4VUserActionInitialization()
{}

//! Class destructor
saunaActionInitialization::~saunaActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void saunaActionInitialization::Build() const
{
  SetUserAction(new saunaPrimaryGeneratorAction());

  saunaRunAction* theRunAction = new saunaRunAction;
  SetUserAction(theRunAction);
  
  saunaEventAction* theEventAction = new saunaEventAction;
  SetUserAction(theEventAction);

  SetUserAction(new saunaTrackingAction(theEventAction));

  SetUserAction(new saunaSteppingAction(theEventAction));
}

void saunaActionInitialization::BuildForMaster() const
{
  SetUserAction(new saunaRunAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
