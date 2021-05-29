/* 
 * LA04StackingAction.hh: Definición la clase
 * LA04StackingAction.
 * 
 * Archivo de ejemplo de Geant4 para la unidad 3
 * del curso de Laboratorio Avanzado ECFM-USAC
 * 
 * Héctor Pérez
 * abril 2021
 * 
 * Basado en el ejemplo B1 de Geant4.10.06.p03
 */

#ifndef LA04StackingAction_h
#define LA04StackingAction_h

#include "globals.hh"
#include "G4UserStackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/* Modification to get total number of Cherenkov photons */
class LA04EventAction;
class G4LogicalVolume;

class LA04StackingAction : public G4UserStackingAction
{
  public:
    LA04StackingAction(LA04EventAction* eventAction);
    virtual ~LA04StackingAction();

  public:
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    virtual void NewStage();
    virtual void PrepareNewEvent();

  private:
    LA04EventAction*  EventAction;
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



#endif