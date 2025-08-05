cmake_minimum_required(VERSION 3.10)

project(labyrinth-game-integration-tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set architecture for Apple Silicon
if(APPLE)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
endif()

# Set PKG_CONFIG_PATH for Homebrew on macOS
if(APPLE)
    set(ENV{PKG_CONFIG_PATH} "/opt/homebrew/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
    # Also add library directory
    link_directories(/opt/homebrew/lib)
endif()

# Find CppUnit
find_package(PkgConfig REQUIRED)
pkg_check_modules(CPPUNIT REQUIRED cppunit)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/../include)
include_directories(${CPPUNIT_INCLUDE_DIRS})

# Source files for the main project (excluding main.cpp)
set(PROJECT_SOURCES
    ../src/Cell.cpp
    ../src/Game.cpp
    ../src/Labyrinth.cpp
    ../src/Player.cpp
    ../src/Minotaur.cpp
    ../src/Logger.cpp
    ../src/items/Item.cpp
    ../src/items/FogOfWar.cpp
    ../src/items/Hummer.cpp
    ../src/items/Shield.cpp
    ../src/items/Sword.cpp
)

# Integration test source files
set(INTEGRATION_TEST_SOURCES
    main.cpp
    GameLabyrinthIntegrationTest.cpp
    GamePlayerIntegrationTest.cpp
    LabyrinthPlayerIntegrationTest.cpp
)

# Create test executable
add_executable(run-integration-tests ${PROJECT_SOURCES} ${INTEGRATION_TEST_SOURCES})

# Link CppUnit libraries
target_link_libraries(run-integration-tests ${CPPUNIT_LIBRARIES})
target_compile_options(run-integration-tests PRIVATE ${CPPUNIT_CFLAGS_OTHER})

# Add test target
enable_testing()
add_test(NAME labyrinth-game-integration-tests COMMAND run-integration-tests)
