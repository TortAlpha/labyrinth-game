#ifndef GAME_LABYRINTH_INTEGRATION_TEST_H
#define GAME_LABYRINTH_INTEGRATION_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Game.h"
#include "Labyrinth.h"

/**
 * @brief Integration tests for Game and Labyrinth interaction
 * 
 * These tests verify that Game and Labyrinth components work correctly together,
 * testing scenarios like game initialization, map generation, player spawning,
 * and game state management.
 */
class GameLabyrinthIntegrationTest : public CPPUNIT_NS::TestFixture {
    
    CPPUNIT_TEST_SUITE(GameLabyrinthIntegrationTest);
    
    // Game initialization and labyrinth generation
    CPPUNIT_TEST(testGameInitializationWithValidLabyrinth);
    CPPUNIT_TEST(testGameInitializationWithDifferentSizes);
    
    // Player and minotaur positioning
    CPPUNIT_TEST(testPlayerSpawnAtLabyrinthEntrance);
    CPPUNIT_TEST(testMinotaurSpawnOnValidPath);
    
    // Item placement integration
    CPPUNIT_TEST(testItemsPlacedOnValidCells);
    CPPUNIT_TEST(testItemsNotPlacedOnWalls);
    
    // Game state and labyrinth interaction
    CPPUNIT_TEST(testGameStateWithValidPath);
    CPPUNIT_TEST(testPlayerMovementInLabyrinth);
    
    // Map rendering and game objects
    CPPUNIT_TEST(testMapRenderingWithGameObjects);
    CPPUNIT_TEST(testFogOfWarIntegration);
    
    CPPUNIT_TEST_SUITE_END();

private:
    Game* game;
    Labyrinth* labyrinth;

public:
    void setUp();
    void tearDown();
    
    // Test methods
    void testGameInitializationWithValidLabyrinth();
    void testGameInitializationWithDifferentSizes();
    void testPlayerSpawnAtLabyrinthEntrance();
    void testMinotaurSpawnOnValidPath();
    void testItemsPlacedOnValidCells();
    void testItemsNotPlacedOnWalls();
    void testGameStateWithValidPath();
    void testPlayerMovementInLabyrinth();
    void testMapRenderingWithGameObjects();
    void testFogOfWarIntegration();
};

#endif // GAME_LABYRINTH_INTEGRATION_TEST_H
