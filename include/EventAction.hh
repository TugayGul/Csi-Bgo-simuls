#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include <vector>

class RunAction;

/// Event action class
///

class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction* runAction);
    virtual ~EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double var) { pEdep += var; }
    void AddWavelength(G4double var) { fIWL = var; }

  private:
    RunAction* fRunAction;
    G4double     pEdep, fIWL;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
