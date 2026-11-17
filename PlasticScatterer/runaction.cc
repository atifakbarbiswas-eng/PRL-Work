#include "runaction.hh"

#include "G4Run.hh"
#include "G4ios.hh"

#include <fstream>
#include <filesystem>

runaction::runaction()
{
    nIncident = 0;
    nCompton = 0;
    nRayleigh = 0;
    nPhoto = 0;
    nTransmit = 0;
}

runaction::~runaction()
{
}

void runaction::BeginOfRunAction(const G4Run*)
{
    nIncident = 0;
    nCompton = 0;
    nRayleigh = 0;
    nPhoto = 0;
    nTransmit = 0;

    G4cout << "\n========== Run Started ==========\n";
}

void runaction::EndOfRunAction(const G4Run*)
{
    // Calculate transmission
    nTransmit = nIncident
              - nCompton
              - nRayleigh
              - nPhoto;

    G4cout << "\n========== Simulation Summary ==========\n";

    G4cout << "Incident photons : " << nIncident << G4endl;
    G4cout << "Compton          : " << nCompton << G4endl;
    G4cout << "Rayleigh         : " << nRayleigh << G4endl;
    G4cout << "Photoelectric    : " << nPhoto << G4endl;
    G4cout << "Transmission     : " << nTransmit << G4endl;

    if (nIncident > 0)
    {
        G4cout << "\nProbabilities\n";

        G4cout << "P(Compton)       = "
               << (G4double)nCompton / nIncident << G4endl;

        G4cout << "P(Rayleigh)      = "
               << (G4double)nRayleigh / nIncident << G4endl;

        G4cout << "P(Photoelectric) = "
               << (G4double)nPhoto / nIncident << G4endl;

        G4cout << "P(Transmission)  = "
               << (G4double)nTransmit / nIncident << G4endl;
    }

    //------------------------------------
    // Write CSV
    //------------------------------------

    bool fileExists = std::filesystem::exists("summary.csv");

    std::ofstream file("summary.csv", std::ios::app);

    if (!fileExists)
    {
        file << "Energy_keV,"
             << "Incident,"
             << "Compton,"
             << "Rayleigh,"
             << "Photoelectric,"
             << "Transmission\n";
    }

    file << 59.54 << ","
         << nIncident << ","
         << nCompton << ","
         << nRayleigh << ","
         << nPhoto << ","
         << nTransmit << "\n";

    file.close();

    G4cout << "\nResults written to summary.csv\n";
    G4cout << "========================================" << G4endl;
}

void runaction::CountIncident()
{
    nIncident++;
}

void runaction::CountCompton()
{
    nCompton++;
}

void runaction::CountRayleigh()
{
    nRayleigh++;
}

void runaction::CountPhoto()
{
    nPhoto++;
}

void runaction::CountTransmit()
{
    nTransmit++;
}
analysis* runaction::GetAnalysis()
{
    return &analysisManager;
}