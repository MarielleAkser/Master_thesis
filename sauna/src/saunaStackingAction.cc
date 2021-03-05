 
/// \file saunaStackingAction.cc
/// \brief Implementation of the saunaStackingAction class

#include "saunaStackingAction.hh"
#include "saunaRunAction.hh"

#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

saunaStackingAction::saunaStackingAction(saunaRunAction* aRunAction) :
G4UserStackingAction(),fRunAction(aRunAction)
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack saunaStackingAction::ClassifyNewTrack (const G4Track*
aTrack)
{
  // Task 4a.1: If the track has energy < 1 MeV, return fKill
 
  // Register only secondaries, i.e. tracks having ParentID > 0
  if (aTrack->GetParentID())
  {
    fRunAction->AddSecondary(aTrack->GetParticleDefinition(),
    aTrack->GetKineticEnergy());
  }
// Do not affect track classification. Just return what would have
// been returned by the base class
return G4UserStackingAction::ClassifyNewTrack(aTrack);
}

