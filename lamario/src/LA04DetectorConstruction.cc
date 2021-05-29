/* 
 * LA04DetectorConstruction.cc: Implementación para la clase
 * LA04DetectorConstrucion.
 * 
 * Archivo de ejemplo de Geant4 para la unidad 3
 * del curso de Laboratorio Avanzado ECFM-USAC
 * 
 * Héctor Pérez
 * abril 2021
 * 
 * Basado en el ejemplo B1 de Geant4.10.06.p03
 */

#include "LA04DetectorConstruction.hh"

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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LA04DetectorConstruction::LA04DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LA04DetectorConstruction::~LA04DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* LA04DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeX = 40*cm;
  G4double world_sizeY = 40*cm;
  G4double world_sizeZ = 40*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeX, 0.5*world_sizeY, 0.5*world_sizeZ);     //its size
      
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
                     
 

  //Envoltura de aluminio

  G4ThreeVector Envpos = G4ThreeVector(0, 0, 37.5*mm);

  G4RotationMatrix *Envrotation = new G4RotationMatrix();
  // Envrotation->rotateY(90.*deg);
  // Envrotation->rotateY(90.*deg);
        
  G4double Env_radius = 12.5*mm;
  G4double Env_height = 75*mm;
  G4Material* Env_mat = nist->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  G4Tubs* solidEnv =    
    new G4Tubs("Env",                       //its namedd
       0, Env_radius, 0.5*Env_height, 0, 360*deg );
                      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,         //its solid
                        Env_mat,          //its material
                        "Env");           //its name

  new G4PVPlacement(Envrotation,                       //no rotation
                    Envpos,                    //at position
                    logicEnv,             //its logical volume
                    "Env",                //its name
                    logicWorld,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking

    
  // Target
   
  G4ThreeVector pos = G4ThreeVector(0, 0, -0.355*cm);
        
  G4double target_radius = 4.5*mm;
  G4double target_height = 67*mm;
  
  //Se cambia el material a CLORO
  G4Material* target_mat = nist->FindOrBuildMaterial("G4_Cl");
  G4Tubs* solidTarget =    
    new G4Tubs("Cloro",                       //its name
       0, target_radius, 0.5*target_height, 0, 360*deg);
                      
  G4LogicalVolume* logicTarget =                         
    new G4LogicalVolume(solidTarget,         //its solid
                        target_mat,          //its material
                        "Cloro");           //its name

  new G4PVPlacement(0,                       //no rotation
                    pos,                    //at position
                    logicTarget,             //its logical volume
                    "Cloro",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  
                
  // Set Target as scoring volume
  //
  fScoringVolume = logicTarget;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
