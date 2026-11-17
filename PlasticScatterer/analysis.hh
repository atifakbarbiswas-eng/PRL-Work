#ifndef ANALYSIS_HH
#define ANALYSIS_HH

#include <fstream>
#include <string>

class analysis
{
public:

    analysis();
    ~analysis();

    void WriteInteraction(
        int eventID,
        double energy,
        double x,
        double y,
        double z,
        double depth,
        const std::string& process);

private:

    std::ofstream interactionFile;
};

#endif