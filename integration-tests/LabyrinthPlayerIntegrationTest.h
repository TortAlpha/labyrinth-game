#ifndef LABYRINTH_PLAYER_INTEGRATION_TEST_H
#define LABYRINTH_PLAYER_INTEGRATION_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Labyrinth.h"
#include "Player.h"

/**
 * @brief Integration tests for Labyrinth and Player interaction
 * 
 * These tests verify that Labyrinth and Player components work correctly together,
 * testing scenarios like player navigation through the labyrinth, boundary validation,
 * pathfinding with player position, and map rendering with player visibility.
 */
class LabyrinthPlayerIntegrationTest : public CPPUNIT_NS::TestFixture {
    
    CPPUNIT_TEST_SUITE(LabyrinthPlayerIntegrationTest);
    
    // Player navigation in labyrinth
    CPPUNIT_TEST(testPlayerNavigationThroughLabyrinth);
    CPPUNIT_TEST(testPlayerBoundaryValidation);
    
    // Player positioning and labyrinth structure
    CPPUNIT_TEST(testPlayerPositionInLabyrinthBounds);
    CPPUNIT_TEST(testPlayerAccessibleCells);
    
    // Pathfinding and player movement
    CPPUNIT_TEST(testPlayerPathFromEntranceToExit);
    CPPUNIT_TEST(testPlayerMovementAlongValidPath);
    
    // Map rendering with player
    CPPUNIT_TEST(testLabyrinthRenderingWithPlayerPosition);
    CPPUNIT_TEST(testFogOfWarWithPlayerMovement);
    
    // Player interaction with labyrinth elements
    CPPUNIT_TEST(testPlayerInteractionWithWalls);
    CPPUNIT_TEST(testPlayerInteractionWithSpecialCells);
    
    CPPUNIT_TEST_SUITE_END();

private:
    Labyrinth* labyrinth;
    Player* player;

public:
    void setUp();
    void tearDown();
    
    // Test methods
    void testPlayerNavigationThroughLabyrinth();
    void testPlayerBoundaryValidation();
    void testPlayerPositionInLabyrinthBounds();
    void testPlayerAccessibleCells();
    void testPlayerPathFromEntranceToExit();
    void testPlayerMovementAlongValidPath();
    void testLabyrinthRenderingWithPlayerPosition();
    void testFogOfWarWithPlayerMovement();
    void testPlayerInteractionWithWalls();
    void testPlayerInteractionWithSpecialCells();
};

#endif // LABYRINTH_PLAYER_INTEGRATION_TEST_H
