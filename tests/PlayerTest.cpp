#include "PlayerTest.h"
#include <cppunit/extensions/HelperMacros.h>

// Register the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(PlayerTest);

void PlayerTest::setUp() {
    player = new Player();
}

void PlayerTest::tearDown() {
    delete player;
    player = nullptr;
}

void PlayerTest::testDefaultConstructor() {
    Player defaultPlayer;
    
    // Test initial position (default Cell constructor creates position (-1,-1) with value '0')
    CPPUNIT_ASSERT_EQUAL(-1, defaultPlayer.getPosition().getRow());
    CPPUNIT_ASSERT_EQUAL(-1, defaultPlayer.getPosition().getCol());
    
    // Test initial effect states (all should be false)
    CPPUNIT_ASSERT(!defaultPlayer.hasSwordEffect());
    CPPUNIT_ASSERT(!defaultPlayer.hasShieldEffect());
    CPPUNIT_ASSERT(!defaultPlayer.hasHummerEffect());
    CPPUNIT_ASSERT(!defaultPlayer.hasFogOfWarEffect());
    
    // Test initial immunity state
    CPPUNIT_ASSERT(!defaultPlayer.isImmuneToMinotaur());
    CPPUNIT_ASSERT_EQUAL(0, defaultPlayer.getImmuneDuration());
}

void PlayerTest::testPositionManagement() {
    Cell newPosition(5, 10, 'P');
    player->setPosition(newPosition);
    
    Cell retrievedPosition = player->getPosition();
    CPPUNIT_ASSERT_EQUAL(5, retrievedPosition.getRow());
    CPPUNIT_ASSERT_EQUAL(10, retrievedPosition.getCol());
    CPPUNIT_ASSERT_EQUAL('P', retrievedPosition.getVal());
}

void PlayerTest::testEffectStatus() {
    // Test sword effect
    player->addSwordEffect();
    CPPUNIT_ASSERT(player->hasSwordEffect());
    player->removeSwordEffect();
    CPPUNIT_ASSERT(!player->hasSwordEffect());
    
    // Test shield effect
    player->addShieldEffect();
    CPPUNIT_ASSERT(player->hasShieldEffect());
    player->removeShieldEffect();
    CPPUNIT_ASSERT(!player->hasShieldEffect());
    
    // Test hammer effect
    player->addHummerEffect();
    CPPUNIT_ASSERT(player->hasHummerEffect());
    player->removeHummerEffect();
    CPPUNIT_ASSERT(!player->hasHummerEffect());
    
    // Test fog of war effect
    player->addFogOfWarEffect();
    CPPUNIT_ASSERT(player->hasFogOfWarEffect());
    player->removeFogOfWarEffect();
    CPPUNIT_ASSERT(!player->hasFogOfWarEffect());
}

void PlayerTest::testImmunitySystem() {
    // Test setting immunity with duration
    player->setImmuneToMinotaur(true, 5);
    
    CPPUNIT_ASSERT(player->isImmuneToMinotaur());
    CPPUNIT_ASSERT_EQUAL(5, player->getImmuneDuration());
    
    // Test decreasing immunity duration
    player->decreaseImmuneDuration();
    CPPUNIT_ASSERT_EQUAL(4, player->getImmuneDuration());
    CPPUNIT_ASSERT(player->isImmuneToMinotaur()); // Should still be immune
    
    // Test immunity expiration
    for (int i = 0; i < 4; i++) {
        player->decreaseImmuneDuration();
    }
    CPPUNIT_ASSERT_EQUAL(0, player->getImmuneDuration());
    CPPUNIT_ASSERT(!player->isImmuneToMinotaur()); // Should no longer be immune
}

void PlayerTest::testMovePlayer() {
    // Movement methods are not directly available in Player class
    // This test would need to be implemented at the Game level
    Cell initialPosition = player->getPosition();
    
    // Test position setting instead
    Cell newPosition(initialPosition.getRow() + 1, initialPosition.getCol(), 'P');
    player->setPosition(newPosition);
    
    Cell retrievedPosition = player->getPosition();
    CPPUNIT_ASSERT_EQUAL(initialPosition.getRow() + 1, retrievedPosition.getRow());
    CPPUNIT_ASSERT_EQUAL(initialPosition.getCol(), retrievedPosition.getCol());
}

void PlayerTest::testEffectToggling() {
    // Test multiple effects can be active simultaneously
    player->addSwordEffect();
    player->addShieldEffect();
    
    CPPUNIT_ASSERT(player->hasSwordEffect());
    CPPUNIT_ASSERT(player->hasShieldEffect());
    CPPUNIT_ASSERT(!player->hasHummerEffect());
    CPPUNIT_ASSERT(!player->hasFogOfWarEffect());
    
    // Test removing effects individually
    player->removeSwordEffect();
    player->removeShieldEffect();
    CPPUNIT_ASSERT(!player->hasSwordEffect());
    CPPUNIT_ASSERT(!player->hasShieldEffect());
    CPPUNIT_ASSERT(!player->hasHummerEffect());
    CPPUNIT_ASSERT(!player->hasFogOfWarEffect());
}
