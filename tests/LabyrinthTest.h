#ifndef LABYRINTHTEST_H
#define LABYRINTHTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../include/Labyrinth.h"

/**
 * @brief Test class for the Labyrinth class.
 * 
 * Tests labyrinth functionality including:
 * - Construction and initialization
 * - Map generation
 * - Path finding
 * - Cell access and modification
 * - Validation of entrance and exit
 */
class LabyrinthTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(LabyrinthTest);
    CPPUNIT_TEST(testDefaultConstructor);
    CPPUNIT_TEST(testParametrizedConstructor);
    CPPUNIT_TEST(testMapGeneration);
    CPPUNIT_TEST(testCellAccess);
    CPPUNIT_TEST(testBoundaryValidation);
    CPPUNIT_TEST(testEntranceAndExit);
    CPPUNIT_TEST(testPathFinding);
    CPPUNIT_TEST(testMapValidation);
    CPPUNIT_TEST_SUITE_END();

private:
    Labyrinth* labyrinth;

public:
    void setUp() override;
    void tearDown() override;

    void testDefaultConstructor();
    void testParametrizedConstructor();
    void testMapGeneration();
    void testCellAccess();
    void testBoundaryValidation();
    void testEntranceAndExit();
    void testPathFinding();
    void testMapValidation();
};

#endif // LABYRINTHTEST_H
