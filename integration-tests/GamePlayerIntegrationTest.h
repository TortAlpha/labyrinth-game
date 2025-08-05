#ifndef GAME_PLAYER_INTEGRATION_TEST_H
#define GAME_PLAYER_INTEGRATION_TEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Game.h"
#include "Player.h"

/**
 * @brief Integration tests for Game and Player interaction
 * 
 * These tests verify that Game and Player components work correctly together,
 * testing scenarios like player movement, collision detection, item effects,
 * and game state changes based on player actions.
 */
class GamePlayerIntegrationTest : public CPPUNIT_NS::TestFixture {
    
    CPPUNIT_TEST_SUITE(GamePlayerIntegrationTest);
    
    // Player initialization and positioning
    CPPUNIT_TEST(testPlayerInitializationInGame);
    CPPUNIT_TEST(testPlayerPositionTracking);
    
    // Player movement integration
    CPPUNIT_TEST(testPlayerMovementCommands);
    CPPUNIT_TEST(testPlayerWallCollision);
    
    // Player effects and items
    CPPUNIT_TEST(testPlayerEffectManagement);
    CPPUNIT_TEST(testPlayerImmunitySystem);
    
    // Game state based on player actions
    CPPUNIT_TEST(testPlayerReachingExit);
    CPPUNIT_TEST(testPlayerMinotaurInteraction);
    
    CPPUNIT_TEST_SUITE_END();

private:
    Game* game;
    Player* player;

public:
    void setUp();
    void tearDown();
    
    // Test methods
    void testPlayerInitializationInGame();
    void testPlayerPositionTracking();
    void testPlayerMovementCommands();
    void testPlayerWallCollision();
    void testPlayerEffectManagement();
    void testPlayerImmunitySystem();
    void testPlayerReachingExit();
    void testPlayerMinotaurInteraction();
};

#endif // GAME_PLAYER_INTEGRATION_TEST_H
