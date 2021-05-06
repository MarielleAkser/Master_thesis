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
#include "G4THitsMap.hh"
#include "globals.hh"
#include "G4Electron.hh"

/// Event action class

class saunaEventAction : public G4UserEventAction
{
  public:
    saunaEventAction();
    ~saunaEventAction();

    virtual void BeginOfEventAction(const G4Event* anEvent) override;
    virtual void EndOfEventAction(const G4Event* anEvent) override;

    void Add_eDep_Beta( G4double eDep, G4String parent_name )
    {
      // When the electron is the mother particle the track ID == 1
      // When gamma is the mother particel the trackID is == 2
      // and when the secondary particle is created from the gamma the track ID will always 
      // be higher than 2.

      fTotalEnergyDeposit_Beta += eDep;

      // if (parent_name == "e-")
      // {
      //   fParentName_Beta = "e-"; // FUNKAR INTE! 
      // }

      // if (trackID == 1)
      // {
      //   fTotalEnergyDeposit_electron += eDep;
      // }
      // if (trackID > 1)
      // {
      //   fTotalEnergyDeposit_gamma += eDep;
  
      // }
    }

    void Add_eDep_NaI( G4double eDep, G4String parent_name )
    {
      fTotalEnergyDeposit_NaI += eDep;
    }

  private:
  // Numerical IDs for hit collections (-1 means unknown yet)
  G4int fshape1ID { -1 };
  G4int fshape2ID { -1 };

  G4double fTotalEnergyDeposit_electron;
  G4double fTotalEnergyDeposit_gamma;

  G4double fTotalEnergyDeposit_Beta;
  G4double fTotalEnergyDeposit_NaI;

  G4String fDetectorName;
  G4String fParticleName;
  G4int fTrackId;
  G4String fParentName_Beta;
  G4String fParentName_NaI;


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
