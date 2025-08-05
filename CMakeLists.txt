cmake_minimum_required(VERSION 3.10)

project(labyrinth-game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set architecture for Apple Silicon
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
endif()

# Main executable
add_executable(labyrinth-game 
	main.cpp 
	src/Cell.cpp 
	src/Game.cpp 
	src/Labyrinth.cpp 
	src/Player.cpp
	include/Input.h
	src/Minotaur.cpp
	src/Logger.cpp
	src/items/Item.cpp
	src/items/FogOfWar.cpp
	src/items/Hummer.cpp
	src/items/Shield.cpp
	src/items/Sword.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Option to build tests
option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()