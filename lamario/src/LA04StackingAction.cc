/* 
 * LA03StackingAction.cc: Implementación para la clase
 * LA03StackingAction.
 * 
 * Archivo de ejemplo de Geant4 para la unidad 3
 * del curso de Laboratorio Avanzado ECFM-USAC
 * 
 * Héctor Pérez
 * abril 2021
 * 
 * Basado en el ejemplo B1 de Geant4.10.06.p03
 */

#include "LA04StackingAction.hh"
#include "LA04EventAction.hh"
#include "LA04DetectorConstruction.hh"

#include "G4VProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


LA04StackingAction::LA04StackingAction(LA04EventAction* eventAction)
  : G4UserStackingAction(),
  EventAction(eventAction)
{}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LA04StackingAction::~LA04StackingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ClassificationOfNewTrack
LA04StackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
     if( aTrack->GetParentID() > 0 )
    {
      //esta condicion es necesaria porque si no se toma en cuenta el evento cero y en ese evento, las particulas primarias parece que no tiene muchos de los atributos aqui usados y saldria error
    
  //      G4cout << "ID: "  << aTrack->GetTrackID()
  //          << " Parent ID: " << aTrack->GetParentID()
  //          << " Particle: " << aTrack->GetDefinition()->GetParticleName()
  //          << " Creation process: " << aTrack->GetCreatorProcess()->GetProcessName()
  //          << " Creation volumen: " << aTrack->GetVolume()->GetName()
  //          << G4endl;
          if(aTrack->GetVolume()->GetName()=="Cloro"){
            // std::cout<<"ESTAMOS EN CLORO";   //DEBUGGING
          // if(aTrack->GetParticleDefinition()->GetParticleName()== "e-"){
            // std::cout<<"Electrón hallado"; //Debugging
          //aqui podemos poner un contador para ir contando cuantos electrones llevamos
          //el contador puede ser como el de distancia o energia profecional que aprendimos a usar
          //o tambien podemos matar a este positron que se creo, para que asi este ya no genere mas particulas
          EventAction->AddNump(1.0);
          return fKill;
          }


        }

      
     
       
  return fUrgent;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LA04StackingAction::NewStage()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LA04StackingAction::PrepareNewEvent()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


