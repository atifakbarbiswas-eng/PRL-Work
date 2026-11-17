# PRL Work

This repository contains the Geant4 simulation work I did during my internship at PRL.

## Projects

### PlasticScatterer

A Geant4 simulation of a plastic scintillator used as a Compton scatterer.

The simulation includes:
- A PVT plastic scintillator
- Particle generation and interaction tracking
- A sensitive detector for recording interactions
- CSV output containing event ID, energy, position, depth and interaction process

The project is built with CMake and requires Geant4 with UI and visualization support.

### ScatPolSim

A Geant4 simulation for the detector setup used for the scattering/polarization study.

The setup includes:
- A plastic scintillator
- A Pb collimator
- A CdTe detector
- A configurable detector arm position
- A gamma-ray source using Geant4 GPS
- Visualization and batch macro files

The current `run1.mac` uses a 59.541 keV polarized gamma-ray source and runs the simulation in batch mode.

## Requirements

- Geant4
- CMake 3.16 or newer
- C++ compiler

## Building

For either project, create a build directory and use CMake:

```bash
mkdir build
cd build
cmake ..
make -j
```

For `ScatPolSim`, the executable is:

```bash
./scatPolSim
```

A batch run can be started with:

```bash
./scatPolSim run1.mac
```

## Repository Structure

```text
PRL-Work/
├── PlasticScatterer/
└── ScatPolSim/
```

This repository contains the simulation code and configuration files used for the PRL project.
