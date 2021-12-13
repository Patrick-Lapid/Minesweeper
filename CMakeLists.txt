cmake_minimum_required(VERSION 3.20)
project(minesweeper)

set(CMAKE_CXX_STANDARD 14)
set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
include_directories(C:/Libraries/SFML-2.5.1/include)

add_executable(minesweeper Toolbox.h Toolbox.cpp main.cpp Tile.cpp Tile.h Button.cpp Button.h GameState.h GameState.cpp minesweeper.h minesweeper.cpp)
target_link_libraries(minesweeper sfml-graphics sfml-audio)