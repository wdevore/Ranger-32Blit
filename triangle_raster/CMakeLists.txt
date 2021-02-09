cmake_minimum_required(VERSION 3.9)

project (triangle)

set(32BLIT_PATH "../../" CACHE PATH "Path to 32blit.cmake")

if(NOT EXISTS ${32BLIT_PATH}/32blit.cmake)
  message(FATAL_ERROR "Define location of 32Blit API with -D32BLIT_PATH=<path to 32blit.cmake>")
endif()

include (${32BLIT_PATH}/32blit.cmake)

blit_executable (${PROJECT_NAME}
    tr.hpp
    tr.cpp
    game/game.hpp
    game/game.cpp
    game/defines.hpp
    game/defines.cpp
    gui/button.hpp
    gui/button.cpp
    geometry/vertex.hpp
    geometry/vertex.cpp
    geometry/triangle.hpp
    geometry/triangle.cpp
    scenes/scene_manager.hpp
    scenes/scene_manager.cpp
    scenes/scene.hpp
    scenes/scene.cpp
    scenes/scene_game.hpp
    scenes/scene_game.cpp
    )
    
blit_metadata (${PROJECT_NAME} metadata.yml)
