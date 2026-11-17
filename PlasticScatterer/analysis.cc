#include "analysis.hh"

analysis::analysis()
{
    interactionFile.open("interaction.csv");

    interactionFile
        << "EventID,"
        << "Energy_keV,"
        << "X_cm,"
        << "Y_cm,"
        << "Z_cm,"
        << "Depth_cm,"
        << "Process\n";
}

analysis::~analysis()
{
    interactionFile.close();
}

void analysis::WriteInteraction(
    int eventID,
    double energy,
    double x,
    double y,
    double z,
    double depth,
    const std::string& process)
{
    interactionFile
        << eventID << ","
        << energy << ","
        << x << ","
        << y << ","
        << z << ","
        << depth << ","
        << process << "\n";
}