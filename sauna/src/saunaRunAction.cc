 
/// \file saunaRunAction.cc
/// \brief Implementation of the saunaEventAction class

#include "saunaRunAction.hh"

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4AccumulableManager.hh"
#include "G4SystemOfUnits.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

saunaRunAction::saunaRunAction() :
 G4UserRunAction(),
 fNGammas("NGammas", 0),
 fNElectrons("NElectrons", 0),
 fAverageGammaEnergy("AvgGammaEnergy",0.),
 fAverageElectronEnergy("AvgElectronEnergy",0.),
 fTotalTrackLength("TotalTrackLength",0.)
 {
    // Register created accumulables
    G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
    accumulableManager->RegisterAccumulable(fNGammas);
    accumulableManager->RegisterAccumulable(fNElectrons);
    accumulableManager->RegisterAccumulable(fAverageGammaEnergy);
    accumulableManager->RegisterAccumulable(fAverageElectronEnergy);
    accumulableManager->RegisterAccumulable(fTotalTrackLength);
 } 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void saunaRunAction::BeginOfRunAction(const G4Run*)
{
  // Reset all accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void saunaRunAction::EndOfRunAction(const G4Run* run)
{
  //retrieve the number of events produced in the run
  G4int nofEvents = run->GetNumberOfEvent();

  //do nothing, if no events were processed
  if (nofEvents == 0) return;

  // Merge accumulables
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  if (IsMaster())
  {
    G4cout
    << "\n--------------------End of Global Run-----------------------"
    << " \n The run was " << nofEvents << " events " << G4endl;
    
    if (fNGammas.GetValue())
    G4cout << " * Produced " << fNGammas.GetValue()/((G4double)nofEvents) <<
    " secondary gammas/event. Average energy: "
    << fAverageGammaEnergy.GetValue()/keV/fNGammas.GetValue() << " keV" << G4endl;
    
    else
    G4cout << " * No secondary gammas produced" << G4endl;
    
    if (fNElectrons.GetValue())
    G4cout << " * Produced " << fNElectrons.GetValue()/((G4double)nofEvents) <<
    " secondary electrons/event. Average energy: "
    << fAverageElectronEnergy.GetValue()/keV/fNElectrons.GetValue() << " keV" << G4endl;
    
    else
    G4cout << " * No secondary electrons produced" << G4endl;
    
    if (fTotalTrackLength.GetValue())
    {
    G4cout << " * Total track length of electrons in 1st absorber: ";
    G4cout << fTotalTrackLength.GetValue() / mm << " mm" << G4endl;
  
    G4double fluence = fTotalTrackLength.GetValue() / (.5 * 10 * 10 * cm3);
    G4cout << " * Mean fluence of electrons in 1st absorber: ";
    G4cout << fluence * cm2 << " cm-2" << G4endl;
    }
    else
    {
    // Probably not implemented (becomes relevant in 4a.2). Keep quiet.
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

saunaRunAction::~saunaRunAction()
{
// Task 4c.3: Uncomment the following 2 lines to enable analysis.
/* G4AnalysisManager* man = G4AnalysisManager::Instance();
man->Write(); */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void saunaRunAction::AddSecondary(const G4ParticleDefinition* particle,
G4double energy)
{
  if (particle == G4Gamma::Definition())
  {
    fNGammas += 1;
    fAverageGammaEnergy += energy;
  }
  else if (particle == G4Electron::Definition())
  {
    fNElectrons += 1;
    fAverageElectronEnergy += energy;
  }
    return;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void saunaRunAction::AddTrackLength(G4double trackLength)
{
  // Task 4a.2: Add the track length to the appropriate parameter
}