#ifndef PLAYERTEST_H
#define PLAYERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../include/Player.h"

/**
 * @brief Test class for the Player class.
 * 
 * Tests player functionality including:
 * - Position management
 * - Effect status (sword, shield, hammer, fog of war)
 * - Immunity system
 * - Item application
 */
class PlayerTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(PlayerTest);
    CPPUNIT_TEST(testDefaultConstructor);
    CPPUNIT_TEST(testPositionManagement);
    CPPUNIT_TEST(testEffectStatus);
    CPPUNIT_TEST(testImmunitySystem);
    CPPUNIT_TEST(testMovePlayer);
    CPPUNIT_TEST(testEffectToggling);
    CPPUNIT_TEST_SUITE_END();

private:
    Player* player;

public:
    void setUp() override;
    void tearDown() override;

    void testDefaultConstructor();
    void testPositionManagement();
    void testEffectStatus();
    void testImmunitySystem();
    void testMovePlayer();
    void testEffectToggling();
};

#endif // PLAYERTEST_H
