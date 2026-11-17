cmake_minimum_required(VERSION 3.16)

project(PlasticScatterer)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

add_executable(PlasticScatterer

    main.cc

    detector.cc
    physics.cc

    actioninitialization.cc

    particlegun.cc

    scattererSD.cc

    runaction.cc
    eventaction.cc
    steppingaction.cc
    analysis.cc
)

target_link_libraries(PlasticScatterer ${Geant4_LIBRARIES})