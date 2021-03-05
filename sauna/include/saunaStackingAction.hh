/// \file saunaStackingAction.hh
/// \brief Definition of the saunaStackingAction class

#ifndef saunaStackingAction_h
#define saunaStackingAction_h 1

#include "G4UserStackingAction.hh"
#include "G4Track.hh"

#include "globals.hh"

class saunaRunAction;

class saunaStackingAction : public G4UserStackingAction
{
  public:
    saunaStackingAction(saunaRunAction* );
    ~saunaStackingAction(){;};

  //! Main interface
    G4ClassificationOfNewTrack ClassifyNewTrack (const G4Track*);
    
    private:
    saunaRunAction* fRunAction;
};

#endif

