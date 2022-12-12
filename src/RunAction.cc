#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "g4root.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
: G4UserRunAction(),
  fEdep1(0.),
  fEdep2(0.)
{ 
  G4RunManager::GetRunManager()->SetPrintProgress(20000000);
  G4String  binSchemeName, fcnName, unitName;
  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager->CreateH1("IWL","Optical Photon Wavelength",600,200*nm,800*nm,unitName = "nm",fcnName = "none",binSchemeName = "linear");

  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fEdep1);
  accumulableManager->RegisterAccumulable(fEdep2); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* run)
{ 
  // inform the runManager to save random number seed
  if (IsMaster()) {
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  }

  auto analysisManager = G4AnalysisManager::Instance();
  G4String fileName = "Result";
  G4int runID = run->GetRunID();
  G4String runIDstr = G4UIcommand::ConvertToString(runID);
  analysisManager->OpenFile(fileName+runIDstr);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Merge accumulables 
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  // Compute total energy deposit in a run and its variance
  //
  if (IsMaster()) {
    G4double tEdep1 = fEdep1.GetValue();
    G4double tEdep2 = fEdep2.GetValue();
  
    G4double rms = tEdep2 - tEdep1*tEdep1/nofEvents;
    if (rms > 0.) rms = std::sqrt(rms); else rms = 0.;  

    G4double ppEdep = tEdep1/nofEvents;
    G4String NofPrimaries = G4UIcommand::ConvertToString(nofEvents)+" Primary Particles";

    Edep.open("Edep.txt",std::ios::app);
    Edep << G4BestUnit(ppEdep,"Energy") <<" "<< G4BestUnit(tEdep1,"Energy") <<" "<< G4BestUnit(rms,"Energy") <<" "<< NofPrimaries << G4endl;
    Edep.close();
  }
        
  // Print
  //  
  if (IsMaster()) {
    G4cout
     << G4endl
     << " The run consists of " << nofEvents << " "
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << " The run consists of " << nofEvents << " "
     << G4endl
     << "--------------------End of Local Run------------------------";
  }
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write(); // automatically merges threads , Ntuples would require merge function.
  analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::AddEdep(G4double var)
{
  fEdep1 += var;
  fEdep2 += var*var;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

