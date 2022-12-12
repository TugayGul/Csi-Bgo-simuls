#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"
#include <fstream>

class G4Run;

/// Run action class
///

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    virtual ~RunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddEdep (G4double var); 

  private:
    G4Accumulable<G4double> fEdep1;
    G4Accumulable<G4double> fEdep2;
    std::ofstream Edep;
};

#endif

