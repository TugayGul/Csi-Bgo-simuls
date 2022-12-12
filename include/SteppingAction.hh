#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class EventAction;
class RunAction;
class DetectorConstruction;

class G4LogicalVolume;

/// Stepping action class
/// 

class SteppingAction : public G4UserSteppingAction
{
  public:
    SteppingAction(const DetectorConstruction* detectorConstruction,RunAction* runAction,EventAction* eventAction);
    virtual ~SteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step* step);

  private:
    const DetectorConstruction* fDetConstruction;
    RunAction* fRunAction;
    EventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
