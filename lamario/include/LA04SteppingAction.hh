/* 
 * LA04SteppingAction.hh: Header para la clase
 * LA04SteppingAction.
 * 
 * Archivo de ejemplo de Geant4 para la unidad 3
 * del curso de Laboratorio Avanzado ECFM-USAC
 * 
 * Héctor Pérez
 * abril 2021
 * 
 * Basado en el ejemplo B1 de Geant4.10.06.p03
 */

#ifndef LA04SteppingAction_h
#define LA04SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class LA04EventAction;

class G4LogicalVolume;

/// Stepping action class
/// 

class LA04SteppingAction : public G4UserSteppingAction
{
  public:
    LA04SteppingAction(LA04EventAction* eventAction);
    virtual ~LA04SteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);

  private:
    LA04EventAction*  fEventAction;
    G4LogicalVolume* fScoringVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
