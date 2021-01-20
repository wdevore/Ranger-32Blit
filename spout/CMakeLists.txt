cmake_minimum_required(VERSION 3.9)

project (spout)

set(32BLIT_PATH "../../" CACHE PATH "Path to 32blit.cmake")

if(NOT EXISTS ${32BLIT_PATH}/32blit.cmake)
  message(FATAL_ERROR "Define location of 32Blit API with -D32BLIT_PATH=<path to 32blit.cmake>")
endif()

include (${32BLIT_PATH}/32blit.cmake)

blit_executable (${PROJECT_NAME}
    spout.cpp
    game/game.cpp
    game/defines.hpp
    game/defines.cpp
    game/ship.hpp
    game/ship.cpp
    game/parameter.hpp
    game/parameter.cpp
    gui/button.hpp
    gui/button.cpp
    particles/particle_node.hpp
    particles/particle_node.cpp
    particles/particle_circle.hpp
    particles/particle_circle.cpp
    particles/particle_square.hpp
    particles/particle_square.cpp
    particles/particle_system.hpp
    particles/particle_system.cpp
    particles/particle_activator.hpp
    particles/particle_activator.cpp
    particles/activator_arc.hpp
    particles/activator_arc.cpp
    particles/activator_radial.hpp
    particles/activator_radial.cpp
    islands/island.hpp
    islands/island.cpp
    islands/islands.hpp
    islands/islands.cpp
    islands/island_buffer.hpp
    islands/island_buffer.cpp
    islands/island_maps.cpp
    scenes/scene_manager.hpp
    scenes/scene_manager.cpp
    scenes/scene.hpp
    scenes/scene.cpp
    scenes/scene_boot.hpp
    scenes/scene_boot.cpp
    scenes/scene_splash.hpp
    scenes/scene_splash.cpp
    scenes/scene_exit.hpp
    scenes/scene_exit.cpp
    scenes/scene_menu.hpp
    scenes/scene_menu.cpp
    scenes/scene_game.hpp
    scenes/scene_game.cpp
    scenes/scene_about.hpp
    scenes/scene_about.cpp
    scenes/scene_scores.hpp
    scenes/scene_scores.cpp
    )
    
blit_metadata (${PROJECT_NAME} metadata.yml)
