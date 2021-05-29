/* 
 * LA04EventAction.cc: Implementación para la clase
 * LA04EventAction.
 * 
 * Archivo de ejemplo de Geant4 para la unidad 3
 * del curso de Laboratorio Avanzado ECFM-USAC
 * 
 * Héctor Pérez
 * abril 2021
 * 
 * Basado en el ejemplo B1 de Geant4.10.06.p03
 */

#include "LA04EventAction.hh"
#include "LA04RunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "g4root.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LA04EventAction::LA04EventAction(LA04RunAction* runAction)
: G4UserEventAction(),
  fRunAction(runAction),
  fEdep(0.),
  fDistance(0.),
  fNump(0.)
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LA04EventAction::~LA04EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LA04EventAction::BeginOfEventAction(const G4Event*)
{    
  fEdep = 0.;   
  fDistance = 0.;
  fNump = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LA04EventAction::EndOfEventAction(const G4Event*)
{   
  // accumulate statistics in run action
  fRunAction->AddEdep(fEdep);
  fRunAction->AddDistance(fDistance);
  fRunAction->AddNump(fNump);

   // Fill histograms
  auto analysisManager = G4AnalysisManager::Instance();
  //analysisManager->FillH1(1, fDistance);   //VAMOS LLENANDO EL HISTOGRAMA A CAAD EVENTO QUE OCURRE
  //analysisManager->FillH1(1, fEdep);  //************** 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
