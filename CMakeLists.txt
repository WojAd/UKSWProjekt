cmake_minimum_required (VERSION 3.12.0)

project(pacman)
set(SFML_DIR "../64SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5.1 COMPONENTS graphics audio window system REQUIRED)
add_executable(pacman main.cpp pacman.cpp duch.cpp mapa.cpp pacman.h duch.h mapa.h Button.h Button.cpp Game.h Game.cpp FilePaths.h Menu.h Menu.cpp)
target_link_libraries(pacman sfml-graphics sfml-audio sfml-window sfml-system)