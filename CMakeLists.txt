cmake_minimum_required(VERSION 3.10)

# Название проекта
project(labirint-game-oop2-siit-2024)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(labirint-game-oop2-siit-2024 
	main.cpp 
	src/Cell.cpp 
	src/Game.cpp 
	src/Labyrinth.cpp 
	src/Stack.cpp
	src/Player.cpp
	include/Input.h
	src/Minotaur.cpp
	src/Logger.cpp)


include_directories(${CMAKE_SOURCE_DIR}/include)