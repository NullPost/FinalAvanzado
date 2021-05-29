/* 
 * LA04PrimaryGeneratorAction.cc: Implementación para la clase
 * LA04PrimaryGeneratorAction.
 * 
 * Archivo de ejemplo de Geant4 para la unidad 3
 * del curso de Laboratorio Avanzado ECFM-USAC
 * 
 * Héctor Pérez
 * abril 2021
 * 
 * Basado en el ejemplo B1 de Geant4.10.06.p03
 */

#include "LA04PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "Randomize.hh"

#include <cmath>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


double angRand ,radRand;

LA04PrimaryGeneratorAction::LA04PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="gamma");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));


  //Energía de la partícula
 fParticleGun->SetParticleEnergy(7.*MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

LA04PrimaryGeneratorAction::~LA04PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void LA04PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of ecah event
  //

  // G4double x0 = 0;
  // G4double y0 = 0;

  /* Punto de lanzamiento aleatorio 
   *
   * El punto de lanzamiento está sobre un cuadrado
   * de tamaño sizeXY pero a un z constante */
  angRand = G4UniformRand()*twopi; //
  // radRand 0.1*cm*G4UniformRand(); // eficiencia de energia
  radRand= 1.5*cm*G4UniformRand();  // eficiencia geometrica
  G4double x0 = radRand*cos(angRand);
  G4double y0 = radRand*sin(angRand);
  G4double z0 = G4UniformRand()*(0.5*mm)-50.5*mm;
  
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  /* Dirección aleatoria */
  /*  NECESARIO PARA EL CALCULO DE EFICIENCIA GEOMETRICA */

  // G4double theta = twopi * G4UniformRand();
  // G4double phi = pi * G4UniformRand();

  // fParticleGun->SetParticleMomentumDirection(G4ThreeVector( std::sin(theta)*std::cos(phi), std::sin(theta)*std::sin(phi), std::cos(theta)));

  /*Generar Energía inicial aleatoria*/
  // fParticleGun->SetParticleEnergy(6. * MeV * G4UniformRand());

  fParticleGun->GeneratePrimaryVertex(anEvent);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

