/* 
 * LA04RunAction.hh: Header para la clase
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

#ifndef LA04RunAction_h
#define LA04RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class G4Run;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class LA04RunAction : public G4UserRunAction
{
  public:
    LA04RunAction();
    virtual ~LA04RunAction();

    // virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

    void AddEdep (G4double edep); 
    void AddDistance (G4double distance); 
    void AddNump (G4double nump);

  private:
    G4Accumulable<G4double> fEdep;
    G4Accumulable<G4double> fDistance;
    G4Accumulable<G4double> fNump;
};

#endif

