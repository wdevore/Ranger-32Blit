cmake_minimum_required(VERSION 3.9)

project (spout)

set(32BLIT_PATH "../../" CACHE PATH "Path to 32blit.cmake")

if(NOT EXISTS ${32BLIT_PATH}/32blit.cmake)
  message(FATAL_ERROR "Define location of 32Blit API with -D32BLIT_PATH=<path to 32blit.cmake>")
endif()

include (${32BLIT_PATH}/32blit.cmake)

blit_executable (${PROJECT_NAME}
    spout.cpp
    game.cpp
    utilities.cpp
    ship.hpp
    ship.cpp
    utilities.hpp
    button.hpp
    button.cpp
    island.hpp
    island.cpp
    particle_node.hpp
    particle_node.cpp
    particle_circle.hpp
    particle_circle.cpp
    particle_square.hpp
    particle_square.cpp
    particle_system.hpp
    particle_system.cpp
    particle_activator.hpp
    particle_activator.cpp
    activator_arc.hpp
    activator_arc.cpp
    activator_radial.hpp
    activator_radial.cpp
    )
    
blit_metadata (${PROJECT_NAME} metadata.yml)
