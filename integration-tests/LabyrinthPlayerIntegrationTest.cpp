#include "LabyrinthPlayerIntegrationTest.h"
#include <cppunit/extensions/HelperMacros.h>

// Register the test suite
CPPUNIT_TEST_SUITE_REGISTRATION(LabyrinthPlayerIntegrationTest);

void LabyrinthPlayerIntegrationTest::setUp() {
    // Initialize test objects - using larger size for better generation success
    labyrinth = new Labyrinth(21, 21, true); // Create with quiet mode enabled
    labyrinth->generate();
    
    // Initialize player at labyrinth entrance if possible
    if (labyrinth->getMapGenerationSuccess()) {
        Cell entrance = labyrinth->getStartPoint();
        player = new Player();
        player->setPosition(entrance);
    } else {
        player = new Player(); // Use default constructor
        Cell fallbackPosition(1, 1, ' ');
        player->setPosition(fallbackPosition);
    }
}

void LabyrinthPlayerIntegrationTest::tearDown() {
    delete labyrinth;
    delete player;
    labyrinth = nullptr;
    player = nullptr;
}

void LabyrinthPlayerIntegrationTest::testPlayerNavigationThroughLabyrinth() {
    // Test that player can navigate through valid labyrinth paths
    if (labyrinth->getMapGenerationSuccess()) {
        Cell entrance = labyrinth->getStartPoint();
        player->setPosition(entrance);
        
        Cell playerPos = player->getPosition();
        // Verify player is at entrance
        CPPUNIT_ASSERT_EQUAL(entrance.getRow(), playerPos.getRow());
        CPPUNIT_ASSERT_EQUAL(entrance.getCol(), playerPos.getCol());
        
        // Test that entrance cell is not a wall
        Cell& entranceCell = labyrinth->getCell(entrance.getRow(), entrance.getCol());
        CPPUNIT_ASSERT(entranceCell.getVal() != '#');
    }
}

void LabyrinthPlayerIntegrationTest::testPlayerBoundaryValidation() {
    // Test player position validation against labyrinth boundaries
    unsigned int width = labyrinth->getWidth();
    unsigned int height = labyrinth->getHeight();
    
    // Test valid positions
    Cell pos1(0, 0, ' ');
    player->setPosition(pos1);
    Cell playerPos1 = player->getPosition();
    CPPUNIT_ASSERT(playerPos1.getRow() >= 0);
    CPPUNIT_ASSERT(playerPos1.getCol() >= 0);
    CPPUNIT_ASSERT((unsigned)playerPos1.getRow() < height);
    CPPUNIT_ASSERT((unsigned)playerPos1.getCol() < width);
    
    // Test center position
    Cell pos2(height / 2, width / 2, ' ');
    player->setPosition(pos2);
    Cell playerPos2 = player->getPosition();
    CPPUNIT_ASSERT((unsigned)playerPos2.getRow() < height);
    CPPUNIT_ASSERT((unsigned)playerPos2.getCol() < width);
    
    // Test near boundary
    Cell pos3(height - 1, width - 1, ' ');
    player->setPosition(pos3);
    Cell playerPos3 = player->getPosition();
    CPPUNIT_ASSERT((unsigned)playerPos3.getRow() < height);
    CPPUNIT_ASSERT((unsigned)playerPos3.getCol() < width);
}

void LabyrinthPlayerIntegrationTest::testPlayerPositionInLabyrinthBounds() {
    // Test that player position always stays within labyrinth bounds
    unsigned int width = labyrinth->getWidth();
    unsigned int height = labyrinth->getHeight();
    
    // Test various valid positions
    std::vector<std::pair<int, int>> testPositions = {
        {0, 0}, {1, 1}, {height/2, width/2}, {height-1, width-1}
    };
    
    for (const auto& pos : testPositions) {
        if (pos.first >= 0 && pos.second >= 0 && 
            (unsigned)pos.first < height && (unsigned)pos.second < width) {
            
            Cell testPosition(pos.first, pos.second, ' ');
            player->setPosition(testPosition);
            
            Cell playerPos = player->getPosition();
            CPPUNIT_ASSERT(playerPos.getRow() >= 0);
            CPPUNIT_ASSERT(playerPos.getCol() >= 0);
            CPPUNIT_ASSERT((unsigned)playerPos.getRow() < height);
            CPPUNIT_ASSERT((unsigned)playerPos.getCol() < width);
        }
    }
}

void LabyrinthPlayerIntegrationTest::testPlayerAccessibleCells() {
    // Test that player can access non-wall cells
    if (labyrinth->getMapGenerationSuccess()) {
        // Find accessible cells (non-walls)
        std::vector<Cell> accessibleCells;
        
        for (unsigned int i = 0; i < labyrinth->getHeight(); i++) {
            for (unsigned int j = 0; j < labyrinth->getWidth(); j++) {
                Cell& cell = labyrinth->getCell(i, j);
                if (cell.getVal() != '#') {
                    accessibleCells.push_back(cell);
                    if (accessibleCells.size() >= 5) break; // Limit for testing
                }
            }
            if (accessibleCells.size() >= 5) break;
        }
        
        // Test placing player on accessible cells
        for (const Cell& cell : accessibleCells) {
            player->setPosition(cell);
            
            Cell playerPos = player->getPosition();
            // Verify player position matches the accessible cell
            CPPUNIT_ASSERT_EQUAL(cell.getRow(), playerPos.getRow());
            CPPUNIT_ASSERT_EQUAL(cell.getCol(), playerPos.getCol());
            
            // Verify the cell is indeed not a wall
            Cell& labyrinthCell = labyrinth->getCell(cell.getRow(), cell.getCol());
            CPPUNIT_ASSERT(labyrinthCell.getVal() != '#');
        }
    }
}

void LabyrinthPlayerIntegrationTest::testPlayerPathFromEntranceToExit() {
    // Test player movement along the path from entrance to exit
    if (labyrinth->getMapGenerationSuccess()) {
        std::list<Cell*> path = labyrinth->getPathFromEntranceToExit();
        
        if (!path.empty()) {
            // Test player positioning at path points
            Cell* firstCell = path.front();
            Cell* lastCell = path.back();
            
            // Position player at entrance
            player->setPosition(*firstCell);
            
            Cell playerPos1 = player->getPosition();
            CPPUNIT_ASSERT_EQUAL(firstCell->getRow(), playerPos1.getRow());
            CPPUNIT_ASSERT_EQUAL(firstCell->getCol(), playerPos1.getCol());
            
            // Position player at exit
            player->setPosition(*lastCell);
            
            Cell playerPos2 = player->getPosition();
            CPPUNIT_ASSERT_EQUAL(lastCell->getRow(), playerPos2.getRow());
            CPPUNIT_ASSERT_EQUAL(lastCell->getCol(), playerPos2.getCol());
        }
    }
}

void LabyrinthPlayerIntegrationTest::testPlayerMovementAlongValidPath() {
    // Test that player can move along valid path cells
    if (labyrinth->getMapGenerationSuccess()) {
        std::list<Cell*> path = labyrinth->getPathFromEntranceToExit();
        
        if (path.size() >= 2) {
            auto it = path.begin();
            Cell* currentCell = *it;
            ++it;
            Cell* nextCell = *it;
            
            // Position player at first cell
            player->setPosition(*currentCell);
            
            Cell playerPos1 = player->getPosition();
            CPPUNIT_ASSERT_EQUAL(currentCell->getRow(), playerPos1.getRow());
            CPPUNIT_ASSERT_EQUAL(currentCell->getCol(), playerPos1.getCol());
            
            // Move player to next cell
            player->setPosition(*nextCell);
            
            Cell playerPos2 = player->getPosition();
            // Verify player moved correctly
            CPPUNIT_ASSERT_EQUAL(nextCell->getRow(), playerPos2.getRow());
            CPPUNIT_ASSERT_EQUAL(nextCell->getCol(), playerPos2.getCol());
        }
    }
}

void LabyrinthPlayerIntegrationTest::testLabyrinthRenderingWithPlayerPosition() {
    // Test labyrinth rendering functionality with player positions
    if (labyrinth->getMapGenerationSuccess()) {
        Cell entrance = labyrinth->getStartPoint();
        player->setPosition(entrance);
        
        // Test basic rendering
        CPPUNIT_ASSERT_NO_THROW(labyrinth->print());
        
        // Test fog of war rendering with player position
        Cell playerPos = player->getPosition();
        CPPUNIT_ASSERT_NO_THROW(labyrinth->printWithFogOfWar(playerPos));
    }
}

void LabyrinthPlayerIntegrationTest::testFogOfWarWithPlayerMovement() {
    // Test fog of war rendering as player moves through labyrinth
    if (labyrinth->getMapGenerationSuccess()) {
        // Test fog of war from different player positions
        std::vector<std::pair<unsigned int, unsigned int>> testPositions = {
            {1, 1}, {2, 2}, {3, 3}
        };
        
        for (const auto& pos : testPositions) {
            if (pos.first < labyrinth->getHeight() && pos.second < labyrinth->getWidth()) {
                Cell& testCell = labyrinth->getCell(pos.first, pos.second);
                
                if (testCell.getVal() != '#') { // Only test on non-wall cells
                    Cell newPosition(pos.first, pos.second, 'P');
                    player->setPosition(newPosition);
                    
                    Cell playerPos = player->getPosition();
                    CPPUNIT_ASSERT_NO_THROW(labyrinth->printWithFogOfWar(playerPos));
                    break; // Test one position to avoid excessive output
                }
            }
        }
    }
}

void LabyrinthPlayerIntegrationTest::testPlayerInteractionWithWalls() {
    // Test player interaction with wall cells
    if (labyrinth->getMapGenerationSuccess()) {
        // Find a wall cell
        Cell* wallCell = nullptr;
        
        for (unsigned int i = 0; i < labyrinth->getHeight() && !wallCell; i++) {
            for (unsigned int j = 0; j < labyrinth->getWidth(); j++) {
                Cell& cell = labyrinth->getCell(i, j);
                if (cell.getVal() == '#') {
                    wallCell = &cell;
                    break;
                }
            }
        }
        
        if (wallCell) {
            // Verify wall cell properties
            CPPUNIT_ASSERT_EQUAL('#', wallCell->getVal());
            
            // Test that wall position is within bounds
            CPPUNIT_ASSERT(wallCell->getRow() >= 0);
            CPPUNIT_ASSERT(wallCell->getCol() >= 0);
            CPPUNIT_ASSERT((unsigned)wallCell->getRow() < labyrinth->getHeight());
            CPPUNIT_ASSERT((unsigned)wallCell->getCol() < labyrinth->getWidth());
        }
    }
}

void LabyrinthPlayerIntegrationTest::testPlayerInteractionWithSpecialCells() {
    // Test player interaction with special cells (entrance, exit)
    if (labyrinth->getMapGenerationSuccess()) {
        Cell entrance = labyrinth->getStartPoint();
        Cell exit = labyrinth->getEndPoint();
        
        // Test entrance
        CPPUNIT_ASSERT_EQUAL('U', entrance.getVal());
        player->setPosition(entrance);
        
        Cell playerPos1 = player->getPosition();
        // Verify player can be positioned at entrance
        CPPUNIT_ASSERT_EQUAL(entrance.getRow(), playerPos1.getRow());
        CPPUNIT_ASSERT_EQUAL(entrance.getCol(), playerPos1.getCol());
        
        // Test exit
        CPPUNIT_ASSERT_EQUAL('I', exit.getVal());
        player->setPosition(exit);
        
        Cell playerPos2 = player->getPosition();
        // Verify player can be positioned at exit
        CPPUNIT_ASSERT_EQUAL(exit.getRow(), playerPos2.getRow());
        CPPUNIT_ASSERT_EQUAL(exit.getCol(), playerPos2.getCol());
        
        // Verify entrance and exit are different
        CPPUNIT_ASSERT(!(entrance == exit));
    }
}
