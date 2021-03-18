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
/// \file saunaEventAction.hh
/// \brief Definition of the saunaEventAction class

#ifndef saunaEventAction_h
#define saunaEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class

class saunaEventAction : public G4UserEventAction
{
  public:
    saunaEventAction();
    ~saunaEventAction();

    void BeginOfEventAction(const G4Event* anEvent) override;
    void EndOfEventAction(const G4Event* anEvent) override;

  //   void AddEdep(G4double edep) { fEdep += edep; }

  private:
  // Numerical IDs for hit collections (-1 means unknown yet)
  G4int fShape1Id { -1 };

  //   saunaRunAction* fRunAction;
  //   G4double fEdep;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
