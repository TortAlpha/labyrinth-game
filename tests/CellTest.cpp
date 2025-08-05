#include "CellTest.h"
#include <cppunit/extensions/HelperMacros.h>

// Register the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(CellTest);

void CellTest::setUp() {
    cell = new Cell();
}

void CellTest::tearDown() {
    delete cell;
    cell = nullptr;
}

void CellTest::testDefaultConstructor() {
    Cell defaultCell;
    CPPUNIT_ASSERT_EQUAL(-1, defaultCell.getRow());
    CPPUNIT_ASSERT_EQUAL(-1, defaultCell.getCol());
    CPPUNIT_ASSERT_EQUAL('0', defaultCell.getVal());
}

void CellTest::testParametrizedConstructor() {
    Cell testCell(5, 10, 'X');
    CPPUNIT_ASSERT_EQUAL(5, testCell.getRow());
    CPPUNIT_ASSERT_EQUAL(10, testCell.getCol());
    CPPUNIT_ASSERT_EQUAL('X', testCell.getVal());
}

void CellTest::testGetters() {
    cell->setRow(3);
    cell->setCol(7);
    cell->setVal('P');
    
    CPPUNIT_ASSERT_EQUAL(3, cell->getRow());
    CPPUNIT_ASSERT_EQUAL(7, cell->getCol());
    CPPUNIT_ASSERT_EQUAL('P', cell->getVal());
}

void CellTest::testSetters() {
    cell->setRow(15);
    cell->setCol(20);
    cell->setVal('M');
    
    CPPUNIT_ASSERT_EQUAL(15, cell->getRow());
    CPPUNIT_ASSERT_EQUAL(20, cell->getCol());
    CPPUNIT_ASSERT_EQUAL('M', cell->getVal());
}

void CellTest::testEquality() {
    Cell cell1(5, 10, 'X');
    Cell cell2(5, 10, 'Y'); // Same position, different value
    Cell cell3(6, 10, 'X'); // Different position, same value
    Cell cell4(5, 10, 'X'); // Same position and value
    
    // Test position equality (assuming equality is based on position)
    CPPUNIT_ASSERT(cell1 == cell2); // Same position
    CPPUNIT_ASSERT(!(cell1 == cell3)); // Different position
    CPPUNIT_ASSERT(cell1 == cell4); // Same position and value
}

void CellTest::testPositionValidation() {
    // Test negative positions
    Cell negativeCell(-1, -5, 'T');
    CPPUNIT_ASSERT_EQUAL(-1, negativeCell.getRow());
    CPPUNIT_ASSERT_EQUAL(-5, negativeCell.getCol());
    
    // Test large positions
    Cell largeCell(1000, 2000, 'L');
    CPPUNIT_ASSERT_EQUAL(1000, largeCell.getRow());
    CPPUNIT_ASSERT_EQUAL(2000, largeCell.getCol());
}
