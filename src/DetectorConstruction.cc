#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4GDMLParser.hh"
#include <cmath>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_size = 1*m;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_size, 0.5*world_size, 0.5*world_size);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Scintillator
  //  
  G4Material* CsI = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");

  //
  G4double energy[2] = {1.2398*eV/0.2, 1.2398*eV/0.8};
  G4double rindex[2] = {2.2, 1.8};
  G4MaterialPropertiesTable *Scint = new G4MaterialPropertiesTable();
  Scint -> AddProperty("RINDEX", energy, rindex, 2);
  CsI -> SetMaterialPropertiesTable(Scint);
  //

  G4Orb* solidScintillator =    
    new G4Orb("Scintillator",                //its name
        1*cm);                               //its size
      
  G4LogicalVolume* logicScintillator =                         
    new G4LogicalVolume(solidScintillator,   //its solid
                        CsI,                 //its material
                        "Scintillator");     //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicScintillator,       //its logical volume
                    "Scintillator",          //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

  // visualization attributes
  logicWorld->SetVisAttributes(G4VisAttributes::Invisible);
                
  // Set Scintillator as scoring volume
  //
  fScoringVolume = logicScintillator;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
