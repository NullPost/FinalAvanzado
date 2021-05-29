/* 
 * LA04RunAction.cc: Implementación para la clase
 * LA04RunAction.
 * 
 * Archivo de ejemplo de Geant4 para la unidad 3
 * del curso de Laboratorio Avanzado ECFM-USAC
 * 
 * Héctor Pérez
 * abril 2021
 * 
 * Basado en el ejemplo B1 de Geant4.10.06.p03
 */

#include "LA04RunAction.hh"
#include "LA04PrimaryGeneratorAction.hh"
#include "LA04DetectorConstruction.hh"
// #include "LA04Run.hh"
#include <fstream>

#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "globals.hh"
#include "g4root.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LA04RunAction::LA04RunAction()
: G4UserRunAction(),
  fEdep(0.),
  fDistance(0.),
  fNump(0.)
  
{ 
  // Register accumulable to the accumulable manager
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->RegisterAccumulable(fEdep);
  accumulableManager->RegisterAccumulable(fDistance);
  accumulableManager->RegisterAccumulable(fNump);


  //ARREGLAR ESTE PESDO

  // Se crea una instancia del G4AnalysisManager
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(0); //cuantos mensages saca en pantalla
  analysisManager->SetFirstH1Id(1);

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LA04RunAction::~LA04RunAction()
{
   // Se elimina la instancia del G4AnalysisManager
  delete G4AnalysisManager::Instance();


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LA04RunAction::BeginOfRunAction(const G4Run*)
{ 
  // inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // reset accumulables to their initial values
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();


  //CREACIÓN DE HISTOGRAMAS


   // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  // Open an output file
  analysisManager->OpenFile("LA04");

  // Creating histograms   //HISTOGRAMA DONDE SE GUARDARAN LOS DATOS.
  analysisManager->CreateH1("LA04","Energia depositada en el detector", 100, 0., 100*MeV);



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LA04RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;

  // Merge accumulables 
  G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Merge();

  G4double edep  = fEdep.GetValue();
  G4double Distance  = fDistance.GetValue();
  G4double Nump  = fNump.GetValue();

  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const LA04PrimaryGeneratorAction* generatorAction
   = static_cast<const LA04PrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;
  if (generatorAction)
  {
    const G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";
    G4double particleEnergy = particleGun->GetParticleEnergy();
    runCondition += G4BestUnit(particleEnergy,"Energy");
  }
        
  // Print
  //  
  if (IsMaster()) {
    G4cout
     << G4endl
     << "--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << G4endl
     << "--------------------End of Local Run------------------------";
  }
  
  G4cout
     << G4endl
     << " The run consists of " << nofEvents << " "<< runCondition
     << G4endl
     << " Energy deposited per run, in scoring volume : " 
     << G4BestUnit(edep,"Energy")
     << " Distance traveled per run, in scoring volume : " 
     << G4BestUnit(Distance,"Length")
     << G4endl
     << "------------------------------------------------------------"
     << G4endl
     << G4endl;


    //ESCRITUTA DE LA EFICIENCIA DE ENERGÍA
      G4cout
     << G4endl
     << " The run consists of " << nofEvents << "  "<< runCondition
     << G4endl
     << "Electrones generados"
     << Nump
     << "Número de eventos"
     << nofEvents
     << " Eficiencia : " 
     << Nump/nofEvents
     << G4endl
     << "------------------------------------------------------------"
     << G4endl
     << G4endl;

//ARREGLAR ESTE PEDO

     // Save histograms
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
        //escribir resultados de eficiencia de energia
        std::ofstream archivo;  // objeto de la clase ofstream
        archivo.open("ef_energia.txt",std::ios::app);
        archivo <<Nump/nofEvents<< std::endl;
        archivo.close();



}











//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LA04RunAction::AddEdep(G4double edep)
{
  fEdep  += edep;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LA04RunAction::AddDistance(G4double distance)
{
  fDistance  += distance;
}

void LA04RunAction::AddNump(G4double nump)
{
  fNump  += nump;
}

