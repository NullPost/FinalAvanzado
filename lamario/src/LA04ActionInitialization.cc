/* 
 * LA04ActionInitialization.cc: Implementación para la clase
 * LA04ActionInitialization.
 * 
 * Archivo de ejemplo de Geant4 para la unidad 3
 * del curso de Laboratorio Avanzado ECFM-USAC
 * 
 * Héctor Pérez
 * abril 2021
 * 
 * Basado en el ejemplo B1 de Geant4.10.06.p03
 */

#include "LA04ActionInitialization.hh"
#include "LA04PrimaryGeneratorAction.hh"
#include "LA04RunAction.hh"
#include "LA04EventAction.hh"
#include "LA04SteppingAction.hh"
#include "LA04StackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LA04ActionInitialization::LA04ActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LA04ActionInitialization::~LA04ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LA04ActionInitialization::BuildForMaster() const
{
  LA04RunAction* runAction = new LA04RunAction;
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LA04ActionInitialization::Build() const
{
  SetUserAction(new LA04PrimaryGeneratorAction);

  LA04RunAction* runAction = new LA04RunAction;
  SetUserAction(runAction);
  
  LA04EventAction* eventAction = new LA04EventAction(runAction);
  SetUserAction(eventAction);
  
  SetUserAction(new LA04SteppingAction(eventAction));
  SetUserAction(new LA04StackingAction(eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
