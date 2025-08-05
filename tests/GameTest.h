#ifndef GAMETEST_H
#define GAMETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../include/Game.h"

/**
 * @brief Test class for the Game class.
 * 
 * Tests game functionality including:
 * - Game initialization
 * - Player and Minotaur spawning
 * - Item spawning and management
 * - Game state management
 * - Collision detection
 * - Win/lose conditions
 */
class GameTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(GameTest);
    CPPUNIT_TEST(testGameInitialization);
    CPPUNIT_TEST(testPlayerSpawning);
    CPPUNIT_TEST(testMinotaurSpawning);
    CPPUNIT_TEST(testItemSpawning);
    CPPUNIT_TEST(testGameStateManagement);
    CPPUNIT_TEST(testPlayerMovement);
    CPPUNIT_TEST(testCollisionDetection);
    CPPUNIT_TEST_SUITE_END();

private:
    Game* game;

public:
    void setUp() override;
    void tearDown() override;

    void testGameInitialization();
    void testPlayerSpawning();
    void testMinotaurSpawning();
    void testItemSpawning();
    void testGameStateManagement();
    void testPlayerMovement();
    void testCollisionDetection();
};

#endif // GAMETEST_H
