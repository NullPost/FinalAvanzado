/* 
 * LA04EventAction.hh: Header para la clase
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


#ifndef LA04EventAction_h
#define LA04EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "g4root.hh"

class LA04RunAction;

/// Event action class
///

class LA04EventAction : public G4UserEventAction
{
  public:
    LA04EventAction(LA04RunAction* runAction);
    virtual ~LA04EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdep += edep; }
    void AddDistance(G4double distance) { fDistance += distance; }
    void AddNump(G4double nump) { fNump += nump; }

  private:
    LA04RunAction* fRunAction;
    G4double     fEdep;
    G4double     fDistance;
    G4double     fNump;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
