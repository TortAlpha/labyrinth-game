#ifndef CELLTEST_H
#define CELLTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../include/Cell.h"

/**
 * @brief Test class for the Cell class.
 * 
 * Tests basic functionality of the Cell class including:
 * - Construction
 * - Getters and setters
 * - Position validation
 * - Equality comparison
 */
class CellTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(CellTest);
    CPPUNIT_TEST(testDefaultConstructor);
    CPPUNIT_TEST(testParametrizedConstructor);
    CPPUNIT_TEST(testGetters);
    CPPUNIT_TEST(testSetters);
    CPPUNIT_TEST(testEquality);
    CPPUNIT_TEST(testPositionValidation);
    CPPUNIT_TEST_SUITE_END();

private:
    Cell* cell;

public:
    void setUp() override;
    void tearDown() override;

    void testDefaultConstructor();
    void testParametrizedConstructor();
    void testGetters();
    void testSetters();
    void testEquality();
    void testPositionValidation();
};

#endif // CELLTEST_H
