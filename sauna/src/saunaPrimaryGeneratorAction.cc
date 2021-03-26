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
/// \file saunaPrimaryGeneratorAction.cc
/// \brief Implementation of the saunaPrimaryGeneratorAction class

#include "saunaPrimaryGeneratorAction.hh"

// #include "G4LogicalVolumeStore.hh"
// #include "G4LogicalVolume.hh"
// #include "G4Box.hh"
// #include "G4RunManager.hh"


// #include "G4GeneralParticleSource.hh"
// #include "G4ParticleTable.hh"
// #include "G4SystemOfUnits.hh"
// #include "G4Event.hh"

// #include "G4ParticleDefinition.hh"

// #include "Randomize.hh"

using namespace std;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

saunaPrimaryGeneratorAction::saunaPrimaryGeneratorAction() : 
  G4VUserPrimaryGeneratorAction()
{
  fGPS = new G4GeneralParticleSource();

  // G4ParticleDefinition* particle;
  // particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
  
  // fGPS->SetParticleDefinition(particle);
  
  // fGPS->GetCurrentSource()->GetEneDist()->SetMonoEnergy(662*keV);
  // fGPS->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
  // fGPS->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(0,0,0));

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

saunaPrimaryGeneratorAction::~saunaPrimaryGeneratorAction()
{
  delete fGPS;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void saunaPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  fGPS->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

