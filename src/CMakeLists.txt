cmake_minimum_required(VERSION 3.18)

if (UNIX)
	message("Detected Linux OS")
	message("Please ensure all SFML dependencies are installed (these can be installed using apt and other major package managers\nand are found at https://github.com/HamishHamiltonSmith/Cpp-Pathfinder#dependencies)")
endif (UNIX)


project(path-finder VERSION 1.0)
include(FetchContent)
set(BUILD_SHARED_LIBS ON)
FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)
add_executable(
 path-finder
 main.cpp
)
target_link_libraries(
 path-finder
 sfml-graphics
)
