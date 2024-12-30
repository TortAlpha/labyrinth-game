#include "Labyrinth.h"
#include "Cell.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <list>
#include <termcolor.hpp>

// Returns an integer in [0..max-1]
static int randomInt(int max) {
    if (max <= 0) return 0;
    return rand() % max;
}

// Returns 1 (true) with probability p, else 0 (false)
static int randomBool(double p) {
    double r = (double)rand() / RAND_MAX;
    return (r < p) ? 1 : 0;
}

/**
 * @brief Constructs a Labyrinth object with the specified width and height.
 * 
 * @param w The width of the labyrinth.
 * @param h The height of the labyrinth.
 * 
 * @details 
 * Initializes the labyrinth grid, sets all cells to walls ('#'), and attempts to generate a valid map.
 * If successful, it finds a path from the entrance to the exit.
 */
Labyrinth::Labyrinth(unsigned int w, unsigned int h)
    : width(w), height(h)
{
    srand(static_cast<unsigned>(time(nullptr)));

    std::cout << "Memory allocation for labyrinth "
              << width << " x " << height << "...\n";

    labyrinth = new Cell*[height];
    for (unsigned int row = 0; row < height; row++) {
        labyrinth[row] = new Cell[width];
        for (unsigned int col = 0; col < width; col++) {
            // By default, set everything to '#'
            labyrinth[row][col] = Cell(row, col, '#');
        }
    }

    std::cout << "Memory allocated.\n";
    mapGeneratedSuccessfully = generate();
    if (mapGeneratedSuccessfully) {
        pathFromEntranceToExit = findPathFromEntranceToExit();
    }
}

/**
 * @brief Destructor for the Labyrinth class.
 * 
 * @details 
 * Deallocates the dynamically allocated labyrinth grid.
 */
Labyrinth::~Labyrinth()
{
    for (unsigned int r = 0; r < height; r++) {
        delete[] labyrinth[r];
    }
    delete[] labyrinth;
}

//------------------------------------------------------------------------------
// Kinda optimization: i want to maximize probability of a path from U to I,
// so i curve the semicircles around U and I therefore clear some space
// for the access to more paths.
//
// Also add the TASK CONDITION: count of wall blocs ('#') must be
// more than 2 * (width + height) to ensure the labyrinth is not trivial.
//
// Radius was set experimentally to 1/12.5 of the minimum dimension.
//
// Below: radius = std::min(height, width) / 12.5;
//------------------------------------------------------------------------------
//
// Create a semicircle around (centerRow, centerCol) with radius.
// If topHalf = true -> carve below centerRow (so the entrance row is not destroyed).
// If topHalf = false -> carve above centerRow (so the exit row is not destroyed).
// I skip the outer boundary (row 0, row height-1, col 0, col width-1)
//
void Labyrinth::createSemicircle(unsigned int centerRow, unsigned int centerCol,
                                 unsigned int radius, bool topHalf)
{
    for (int rr = static_cast<int>(centerRow) - static_cast<int>(radius);
             rr <= static_cast<int>(centerRow) + static_cast<int>(radius);
             rr++)
    {
        for (int cc = static_cast<int>(centerCol) - static_cast<int>(radius);
                 cc <= static_cast<int>(centerCol) + static_cast<int>(radius);
                 cc++)
        {
            // Check boundary: skip if it's going out of perimeter
            if (rr <= 0 || rr >= static_cast<int>(height) - 1 ||
                cc <= 0 || cc >= static_cast<int>(width)  - 1)
            {
                continue;
            }

            double dist = std::sqrt(
                std::pow(rr - static_cast<int>(centerRow), 2) +
                std::pow(cc - static_cast<int>(centerCol), 2)
            );
            if (dist <= static_cast<double>(radius)) {

                // If topHalf=true, carve cells if rr >= centerRow
                // so the row with 'U' remains intact. 
                if (topHalf) {
                    if (rr >= static_cast<int>(centerRow)) {
                        labyrinth[rr][cc].setVal(' ');
                    }
                }
                // else for exit. 
                else {
                    // If topHalf=false, carve cells if rr <= centerRow
                    // so the row with 'I' remains intact.
                    if (rr <= static_cast<int>(centerRow)) {
                        labyrinth[rr][cc].setVal(' ');
                    }
                }
            }
        }
    }
}

//------------------------------------------------------------------------------
// I've decided to use BFS for the pathfinding, so I can guarantee a path
//------------------------------------------------------------------------------
//
// BFS: is there a path from (sr,sc) to (er,ec)?
//
bool Labyrinth::isPathExists(unsigned int sr, unsigned int sc,
                             unsigned int er, unsigned int ec)
{
    std::queue<std::pair<int,int>> q;
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

    q.push({ static_cast<int>(sr), static_cast<int>(sc) });
    visited[sr][sc] = true;

    const int DR[4] = { -1, 1,  0, 0 };
    const int DC[4] = {  0, 0, -1, 1 };

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if ((unsigned int)r == er && (unsigned int)c == ec) {
            return true;
        }
        for (int i = 0; i < 4; i++) {
            int nr = r + DR[i];
            int nc = c + DC[i];
            if (nr >= 0 && nr < (int)height &&
                nc >= 0 && nc < (int)width &&
                !visited[nr][nc] &&
                labyrinth[nr][nc].getVal() != '#')
            {
                visited[nr][nc] = true;
                q.push({ nr, nc });
            }
        }
    }
    return false;
}

// wallCondition: count of wall blocs ('#') must be more than 2 * (width + height)
bool Labyrinth::wallCondition()
{
    unsigned int wallCount = 0;
    for (unsigned int r = 1; r < height - 1; r++) {
        for (unsigned int c = 1; c < width - 1; c++) {
            if (labyrinth[r][c].getVal() == '#') {
                wallCount++;
            }
        }
    }
    return wallCount > 2 * (width + height);
}

//------------------------------------------------------------------------------
// I've decided to use algorithm which is a mix of Eller's algorithm and my own
// ideas, so I can guarantee a path from U to I with limited attempts.
//------------------------------------------------------------------------------
//
// Main generation: 1) Eller's-like, 2) semicircles, 3) BFS
//
bool Labyrinth::generate()
{
    const unsigned int MAX_ATTEMPTS = 100;
    bool success = false;

    for (unsigned int attempt = 1; attempt <= MAX_ATTEMPTS && !success; attempt++)
    {
        // Reset labyrinth to '#'
        for (unsigned int r = 0; r < height; r++) {
            for (unsigned int c = 0; c < width; c++) {
                labyrinth[r][c].setVal('#');
            }
        }

        // Set 'U' and 'I' at random columns
        unsigned int enterCol = 1 + randomInt(width / 2 - 1);
        labyrinth[0][enterCol].setVal('U');

        unsigned int exitCol = width / 2 + randomInt(width / 2 - 1);
        labyrinth[height - 1][exitCol].setVal('I');

        // Set start point as the cell below 'U'
        this->startPoint = labyrinth[0][enterCol];
        this->endPoint = labyrinth[height - 1][exitCol];

        // 1) Eller's-like generation in [1..height-2][1..width-2]
        {
            unsigned int innerRows = height - 2;
            unsigned int innerCols = width - 2;
            std::vector<int> currentSet(innerCols, 0), nextSet(innerCols, 0);

            int uniqueSetId = 1;

            auto mergeSets = [&](std::vector<int>& rowSet, int fromId, int toId) {
                for (unsigned int i = 0; i < rowSet.size(); i++) {
                    if (rowSet[i] == fromId) {
                        rowSet[i] = toId;
                    }
                }
            };

            auto carveInner = [&](unsigned int rr, unsigned int cc) {
                if (rr >= 1 && rr <= height - 2 &&
                    cc >= 1 && cc <= width - 2)
                {
                    labyrinth[rr][cc].setVal(' ');
                }
            };

            // Initialize row = 1
            for (unsigned int c = 0; c < innerCols; c++) {
                currentSet[c] = uniqueSetId++;
                if (randomBool(0.3)) {
                    carveInner(1, c + 1);
                }
            }

            // For each row in [1..height-3]
            for (unsigned int row = 1; row < (height - 2); row++) {
                // Horizontal merges
                for (unsigned int c = 0; c < innerCols - 1; c++) {
                    if (currentSet[c] != currentSet[c+1]) {
                        if (randomBool(0.55)) {
                            int oldSet = currentSet[c+1];
                            int newSet = currentSet[c];
                            mergeSets(currentSet, oldSet, newSet);
                            // optionally carve horizontally
                        }
                    }
                }

                // Prepare nextSet
                for (unsigned int i = 0; i < innerCols; i++) {
                    nextSet[i] = 0;
                }
                std::vector<bool> hasDown(innerCols, false);

                // Random vertical pass
                for (unsigned int c = 0; c < innerCols; c++) {
                    if (randomBool(0.5)) {
                        carveInner(row + 1, c + 1);
                        nextSet[c] = currentSet[c];
                        hasDown[c] = true;
                    }
                }

                // Guarantee each set has at least one downward connection,
                // so we can reach the last row.
                for (unsigned int c = 0; c < innerCols; c++) {
                    int setId = currentSet[c];
                    bool found = false;
                    for (unsigned int x = 0; x < innerCols; x++) {
                        if (nextSet[x] == setId) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        carveInner(row + 1, c + 1);
                        nextSet[c] = setId;
                        hasDown[c] = true;
                    }
                }

                // Assign new IDs
                for (unsigned int c = 0; c < innerCols; c++) {
                    if (nextSet[c] == 0) {
                        nextSet[c] = uniqueSetId++;
                    }
                }

                currentSet = nextSet;
            }

            // Last row (height-2)
            // also do it for maximizing probability of a path from U to I
            unsigned int lastInnerRow = height - 2;
            for (unsigned int c = 0; c < innerCols - 1; c++) {
                if (currentSet[c] != currentSet[c+1]) {
                    int oldSet = currentSet[c+1];
                    int newSet = currentSet[c];
                    mergeSets(currentSet, oldSet, newSet);
                    // partial horizontal carve
                    if (randomBool(0.5)) {
                        carveInner(lastInnerRow, c + 1);
                        carveInner(lastInnerRow, c + 2);
                    }
                }
            }

        }

        // 2) Now carve semicircles around 'U' and 'I'
        {
            // Experimentally set radius to 1/12.5 of the minimum dimension
            unsigned int semiRadius = std::min(height, width) / 12.5;
            
            // For the entrance 'U' at (0, enterCol)
            if (height > 1) {
                createSemicircle(1, enterCol, semiRadius, true);
            }

            // For the exit 'I' at (height-1, exitCol)
            if (height > 2) {
                createSemicircle(height - 2, exitCol, semiRadius, false);
            }
        }

        // 3) BFS from (1, enterCol) to (height-2, exitCol)
        unsigned int startRow = 1;
        unsigned int startCol = enterCol;
        unsigned int endRow = height - 2;
        unsigned int endCol = exitCol;

        if (!isPathExists(startRow, startCol, endRow, endCol)) {
            std::cout << "No path from U to I on attempt "
                      << attempt << " / " << MAX_ATTEMPTS << ". Retrying...\n";
        } else {
            std::cout << "Path from U to I found on attempt "
                      << attempt << ".\n";
            success = true;

            if (!wallCondition()) {
                std::cout << "Wall condition not met, retrying...\n";
                success = false;
            } else {
                std::cout << "Wall condition met.\n";
                std::cout << termcolor::green << "Labyrinth generated successfully.\n" << termcolor::reset;
            }
        }

    } // end attempts

    if (!success) {
        std::cout << "Too many attempts, giving up.\n";
        std::cout << termcolor::red << "Labyrinth generation failed.\n" << termcolor::reset;
    }

    // Find a path from 'U' to 'I' and store it in pathFromEntranceToExit
    // for future use in Minotavr logic
    //
    // I could use the reversed path-generation in
    // isPathExists() or in generate() above but
    // I needed to be sure that the path is guaranteed,
    // so I made another BFS function for that.
    //
    this->pathFromEntranceToExit = this->findPathFromEntranceToExit();
    return success;
}

void Labyrinth::print()
{
    for (unsigned int r = 0; r < height; r++) {
        for (unsigned int c = 0; c < width; c++) {
            switch (labyrinth[r][c].getVal())
            {
            case 'U':
                std::cout << termcolor::green << 'U' << termcolor::reset;
                break;
            case 'I':
                std::cout << termcolor::on_green << 'I' << termcolor::reset;
                break;
            case 'R':
                std::cout << termcolor::on_bright_blue << 'R' << termcolor::reset;
                break;
            case 'P':
                std::cout << termcolor::yellow << 'P' << termcolor::reset;
                break;
            case 'M':
                std::cout << termcolor::on_bright_red << 'M' << termcolor::reset;
                break;
            default:
                std::cout << labyrinth[r][c];
                break;
            }
            
        }
        std::cout << "\n";
    }
}

void Labyrinth::saveToFile(const std::string& filename)
{
    std::ofstream file(filename, std::ios::out);
    if (file.is_open()) {
        for (unsigned int r = 0; r < height; r++) {
            for (unsigned int c = 0; c < width; c++) {
                file << labyrinth[r][c].getVal();
            }
            file << "\n";
        }
        file.close();
    }
}

void Labyrinth::printWithFogOfWar(const Cell& playerPos)
{       
    int fogRadius = 1;
    for (unsigned int r = 0; r < height; r++) {
        for (unsigned int c = 0; c < width; c++) {
            if (std::abs((int)r - (int)playerPos.getRow()) <= fogRadius &&
                std::abs((int)c - (int)playerPos.getCol()) <= fogRadius || r == 0 || r == height - 1 || c == 0 || c == width - 1)
            {
                switch (labyrinth[r][c].getVal())
                {
                case 'U':
                    std::cout << termcolor::green << 'U' << termcolor::reset;
                    break;
                case 'I':
                    std::cout << termcolor::on_green << 'I' << termcolor::reset;
                    break;
                case 'R':
                    std::cout << termcolor::on_bright_blue << 'R' << termcolor::reset;
                    break;
                case 'P':
                    std::cout << termcolor::yellow << 'P' << termcolor::reset;
                    break;
                case 'M':
                    std::cout << termcolor::on_bright_red << 'M' << termcolor::reset;
                    break;
                default:
                    std::cout << labyrinth[r][c];
                    break;
                }
            } else {
                std::cout << ' ';
            }
        }
        std::cout << "\n";
    }
}

void Labyrinth::setCell(unsigned int row, unsigned int col, const Cell& cell)
{
    if (row < height && col < width) {
        labyrinth[row][col] = cell;
    }
}

/**
 * @brief Retrieves a reference to the specified cell in the labyrinth.
 * 
 * @param row The row index of the cell.
 * @param col The column index of the cell.
 * @return Cell& Reference to the specified cell.
 */
Cell& Labyrinth::getCell(unsigned int row, unsigned int col) const
{
    return labyrinth[row][col];
}

Cell Labyrinth::getStartPoint()
{
    return this->startPoint;
}

bool Labyrinth::getMapGenerationSuccess()
{
    return mapGeneratedSuccessfully;
}

unsigned int Labyrinth::getWidth()
{
    return this->width;
}

unsigned int Labyrinth::getHeight()
{
    return this->height;
}

//------------------------------------------------------------------------------
// BFS: find a path from entrance 'U' to exit 'I'
//------------------------------------------------------------------------------
//
// Since the labyrinth has been generated successfully, we can guarantee a path.
// So we can use BFS to find a path from 'U' to 'I'.
//
std::list<Cell*> Labyrinth::findPathFromEntranceToExit()
{
    int startR = startPoint.getRow();
    int startC = startPoint.getCol();
    int endR = endPoint.getRow();
    int endC = endPoint.getCol();

    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

    // Parent array for path reconstruction
    std::vector<std::vector<Cell*>> parent(
        height,
        std::vector<Cell*>(width, nullptr)
    );

    //
    // I've decided to store pointers to Cell objects in the queue
    // so in future I can easily reconstruct the path and store it in class.
    //
    Cell* startCell = &labyrinth[startR][startC];
    Cell* endCell = &labyrinth[endR][endC];

    std::queue<Cell*> q;

    q.push(startCell);
    visited[startR][startC] = true;

    const int DR[4] = {-1, 1, 0, 0};
    const int DC[4] = { 0, 0,-1, 1};

    bool found = false;

    // Basic BFS for pathfinding and filling the parent array
    while (!q.empty())
    {
        Cell* current = q.front();
        q.pop();

        int curR = current->getRow();
        int curC = current->getCol();

        if (current == endCell) {
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int nr = curR + DR[i];
            int nc = curC + DC[i];

            if (nr >= 0 && nr < (int)height &&
                nc >= 0 && nc < (int)width &&
                !visited[nr][nc] &&
                labyrinth[nr][nc].getVal() != '#')
            {
                visited[nr][nc] = true;
                parent[nr][nc] = current;
                q.push(&labyrinth[nr][nc]);
            }
        }
    }

    // Here I reconstruct the path from 'U' to 'I' 
    // using parent array made in BFS
    std::list<Cell*> path;
    if (found) {
        Cell* p = endCell;

        while (p != startCell) {
            path.push_front(p);
            p = parent[p->getRow()][p->getCol()];
        }
        path.push_front(startCell);
    }

    return path; 
}

Cell Labyrinth::getEndPoint()
{
    return this->endPoint;
}

std::list<Cell*> Labyrinth::getPathFromEntranceToExit()
{
    return this->pathFromEntranceToExit;
}