#include "PhysicsList.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

#include "G4ProcessManager.hh"
#include "G4Threading.hh"

// Particles
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

// EM Physics Lists
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"

// EM options
#include "G4EmProcessOptions.hh"

// Hadronic and Extra Physics Lists
#include "G4EmExtraPhysics.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4HadronPhysicsQGSP_BIC_AllHP.hh"
#include "G4HadronPhysicsFTFP_BERT_HP.hh"
#include "G4HadronPhysicsINCLXX.hh"
#include "G4HadronElasticPhysicsPHP.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4IonPhysicsPHP.hh"
#include "G4IonINCLXXPhysics.hh"
#include "G4StoppingPhysics.hh"

// Optical processes
#include "G4OpticalPhysics.hh"
#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpMieHG.hh"
#include "G4OpBoundaryProcess.hh"

// Decays
#include "G4Decay.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4PhysicsListHelper.hh"
#include "G4RadioactiveDecayBase.hh"
#include "G4NuclideTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::PhysicsList()
:G4VModularPhysicsList()
{
  G4int verb = 1;
  SetVerboseLevel(verb);

  // add new units
  //
  new G4UnitDefinition( "millielectronVolt", "meV", "Energy", 1.e-3*eV);   

  // add new units for radioActive decays
  // 
  const G4double minute = 60*second;
  const G4double hour   = 60*minute;
  const G4double day    = 24*hour;
  const G4double year   = 365*day;
  new G4UnitDefinition("minute", "min", "Time", minute);
  new G4UnitDefinition("hour",   "h",   "Time", hour);
  new G4UnitDefinition("day",    "d",   "Time", day);
  new G4UnitDefinition("year",   "y",   "Time", year);

  //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  // EM Physics
  RegisterPhysics(new G4EmStandardPhysics_option4(verb));
  RegisterPhysics(new G4EmExtraPhysics(verb));

  // Hadron Elastic Scattering
  RegisterPhysics( new G4HadronElasticPhysicsPHP(verb) );
  
  // Hadron Inelastic Physics
  //RegisterPhysics( new G4HadronPhysicsFTFP_BERT_HP(verb));
  //RegisterPhysics( new G4HadronPhysicsQGSP_BIC_AllHP(verb));
  RegisterPhysics( new G4HadronInelasticQBBC(verb));        
  //RegisterPhysics( new G4HadronPhysicsINCLXX(verb));
  
  // Ion Physics
  RegisterPhysics( new G4IonPhysicsPHP(verb));
  //RegisterPhysics( new G4IonINCLXXPhysics(verb));
  
  // Stopping Particles
  RegisterPhysics( new G4StoppingPhysics(verb));

  // Optical processes
  RegisterPhysics( new G4OpticalPhysics(verb));

  // Decay
  RegisterPhysics(new G4DecayPhysics());

  // Radioactive Decay
  //RegisterPhysics(new G4RadioactiveDecayPhysics());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PhysicsList::~PhysicsList()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetDefaultCutsValue()
{
  // define and set a new default cuts value
  defaultCutValue = 1*um;
  SetDefaultCutValue(defaultCutValue);       
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PhysicsList::SetCuts()
{
  // set the default cuts value for all particle types  
  SetCutsWithDefault();       

  //SetCutValue(0.1*mm, "gamma");
  //SetCutValue(0.1*mm, "e-");
  //SetCutValue(0.1*mm, "e+");
  //SetCutValue(0.1*mm, "proton");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
