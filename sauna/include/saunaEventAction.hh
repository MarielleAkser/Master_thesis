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

    // void Tracks_Created ( G4int trackID, G4int nrSecondaries)
    // {}

    void Add_eDep_NaI( G4double eDep, G4int trackID , G4int parentID, G4String particle_name  )
    {
      if (trackID >= fNrOfParticlesInAnEvent)
      {
        fTotalEnergyDeposit_NaI_Particle1 += eDep;

        if (parentID == 0 )
        {
          fParticle1NaI = particle_name;
        }
      }

      if (trackID - (fNrOfParticlesInAnEvent - 1) == 0)
      {
        fTotalEnergyDeposit_NaI_Particle2 += eDep;

        if (parentID == 0 )
        {
          fParticle2NaI = particle_name;
        }
      }

      if (trackID - (fNrOfParticlesInAnEvent - 2) == 0)
      {
        fTotalEnergyDeposit_NaI_Particle3 += eDep;

        if (parentID == 0 )
        {
          fParticle3NaI = particle_name;
        }
      }

    }


    void Add_eDep_Beta( G4double eDep, G4int trackID , G4int parentID, G4String particle_name  )
    {
      // When the electron is the mother particle the track ID == 1
      // When gamma is the mother particel the trackID is == 2
      // and when the secondary particle is created from the gamma the track ID will always 
      // be higher than 2.

      if (trackID >= fNrOfParticlesInAnEvent)
      {
        fTotalEnergyDeposit_Beta_Particle1 += eDep;

        if (parentID == 0 )
        {
          fParticle1Beta = particle_name;
        }
      }

      if (trackID - (fNrOfParticlesInAnEvent - 1) == 0)
      {
        fTotalEnergyDeposit_Beta_Particle2 += eDep;

        if (parentID == 0 )
        {
          fParticle2Beta = particle_name;
        }
      }

      if (trackID - (fNrOfParticlesInAnEvent - 2) == 0)
      {
        fTotalEnergyDeposit_Beta_Particle3 += eDep;

        if (parentID == 0 )
        {
          fParticle3Beta = particle_name;
        }
      }

    }

    

  private:
  // Numerical IDs for hit collections (-1 means unknown yet)
  G4int fshape1ID { -1 };
  G4int fshape2ID { -1 };

  G4String fParticle1NaI {" "};
  G4String fParticle2NaI {" "};
  G4String fParticle3NaI {" "};

  G4String fParticle1Beta {" "};
  G4String fParticle2Beta {" "};
  G4String fParticle3Beta {" "};

  G4double fTotalEnergyDeposit_Beta_Particle1 { 0 };
  G4double fTotalEnergyDeposit_Beta_Particle2 { 0 };
  G4double fTotalEnergyDeposit_Beta_Particle3 { 0 };

  G4double fTotalEnergyDeposit_NaI_Particle1 { 0 };
  G4double fTotalEnergyDeposit_NaI_Particle2 { 0 };
  G4double fTotalEnergyDeposit_NaI_Particle3 { 0 };

  G4int fNrOfParticlesInAnEvent { 0 };


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
