cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(ScatPolSim)

# Geant4 setup. UI_USE / Vis_use are bundled into the standard
# COMPONENTS request so Qt/OpenGL UI and visualization drivers are
# pulled in if your Geant4 build has them.
option(WITH_GEANT4_UIVIS "Build with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${Geant4_INCLUDE_DIR}
)

file(GLOB sources "${PROJECT_SOURCE_DIR}/*.cc")
file(GLOB headers "${PROJECT_SOURCE_DIR}/*.hh")

list(REMOVE_ITEM sources "${PROJECT_SOURCE_DIR}/main.cc")

add_executable(scatPolSim
    main.cc
    ${sources}
)
target_link_libraries(scatPolSim ${Geant4_LIBRARIES})

# Copy macro files into the build directory so the executable can find
# vis.mac / run macros without needing an absolute path.
set(SCATPOL_SCRIPTS
  vis.mac
  init_vis.mac
  run1.mac
)
foreach(_script ${SCATPOL_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
  )
endforeach()


