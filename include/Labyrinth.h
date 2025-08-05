#ifndef LABYRINTH_H
#define LABYRINTH_H

#include "Cell.h"
#include <list>

/**
 * @brief The Labyrinth class represents the game map consisting of cells arranged in a grid.
 * 
 * @details 
 * Manages the creation, generation, and manipulation of the labyrinth. Handles pathfinding
 * between the entrance ('U') and exit ('I') using BFS to ensure a valid path exists. Provides
 * functionalities to print the labyrinth with or without the fog of war effect.
 * 
 * Author: Roman Avanesov
 * Created: 25.12.2024
 * Last Modified: 30.12.2024
 */
class Labyrinth
{
private:
    unsigned int width;                       ///< The width of the labyrinth.
    unsigned int height;                      ///< The height of the labyrinth.

    bool mapGeneratedSuccessfully = false;    ///< Flag indicating if the map was generated successfully.

    Cell startPoint;                          ///< The starting point ('U') of the labyrinth.
    Cell endPoint;                            ///< The ending point ('I') of the labyrinth.

    Cell** labyrinth;                         ///< 2D array representing the labyrinth grid.

    std::list<Cell*> pathFromEntranceToExit;  ///< List of cells representing the path from entrance to exit.
    
    bool quietMode = false;                   ///< Flag to suppress debug output during tests
    
    uint64_t generation_time = 0;                  ///< Time taken to generate the labyrinth in milliseconds

    /**
     * @brief Finds a path from the entrance to the exit using BFS.
     * 
     * @return std::list<Cell*> The list of cells forming the path.
     */
    std::list<Cell*> findPathFromEntranceToExit();
    
    /**
     * @brief Creates a semicircle around a specified center to carve out paths.
     * 
     * @param centerRow The row index of the semicircle's center.
     * @param centerCol The column index of the semicircle's center.
     * @param radius The radius of the semicircle.
     * @param topHalf If true, carves the top half; otherwise, carves the bottom half.
     */
    void createSemicircle(unsigned int centerRow, unsigned int centerCol,
                          unsigned int radius, bool topHalf);
    
    /**
     * @brief Checks if a path exists between two points using BFS.
     * 
     * @param sr Starting row index.
     * @param sc Starting column index.
     * @param er Ending row index.
     * @param ec Ending column index.
     * 
     * @return true If a path exists.
     * @return false Otherwise.
     */
    bool isPathExists(unsigned int sr, unsigned int sc,
                      unsigned int er, unsigned int ec);
    
    /**
     * @brief Validates the wall condition to ensure labyrinth complexity.
     * 
     * @details 
     * Ensures that the number of wall blocks ('#') is more than twice the sum of width and height,
     * preventing the labyrinth from being too trivial.
     * 
     * @return true If the wall condition is met.
     * @return false Otherwise.
     */
    bool wallCondition();

public:

    /**
     * @brief Default constructor for the Labyrinth class.
     * 
     * @details 
     * Initializes a labyrinth with default dimensions.
     */
    Labyrinth();
    
    /**
     * @brief Parameterized constructor for the Labyrinth class.
     * 
     * @param width The width of the labyrinth.
     * @param height The height of the labyrinth.
     * 
     * @details 
     * Initializes the labyrinth with specified dimensions and generates the map.
     */
    Labyrinth(unsigned int width, unsigned int height);

    /**
     * @brief Constructs a Labyrinth object with the specified width, height and quiet mode.
     * 
     * @param w The width of the labyrinth.
     * @param h The height of the labyrinth.
     * @param quiet Whether to suppress debug output.
     */
    Labyrinth(unsigned int w, unsigned int h, bool quiet);
    
    /**
     * @brief Destructor for the Labyrinth class.
     * 
     * @details 
     * Deallocates the dynamically allocated labyrinth grid.
     */
    ~Labyrinth();
    
    /**
     * @brief Generates the labyrinth map.
     * 
     * @return true If the labyrinth was generated successfully.
     * @return false Otherwise.
     * 
     * @details 
     * Attempts to generate the labyrinth using a combination of Eller's algorithm and
     * custom modifications to ensure a valid path exists between entrance and exit.
     */
    bool generate();
    
    /**
     * @brief Prints the entire labyrinth to the console.
     * 
     * @details 
     * Displays the labyrinth with all cells visible, including game objects.
     */
    void print();
	
	 /**
     * @brief Save the entire labyrinth to the file.
     * 
     * @details 
     * Save the labyrinth with all cells visible, including game objects.
     */
	void saveToFile(const std::string& filename);
    
    /**
     * @brief Prints the labyrinth with a fog of war effect based on the player's position.
     * 
     * @param playerPos The current position of the player.
     * 
     * @details 
     * Limits the visibility of the labyrinth to a 3x3 area around the player, hiding other areas.
     */
    void printWithFogOfWar(const Cell& playerPos);

    /**
     * @brief Retrieves the end point ('I') of the labyrinth.
     * 
     * @return Cell The end point of the labyrinth.
     */
    Cell getEndPoint();
    
    /**
     * @brief Retrieves the start point ('U') of the labyrinth.
     * 
     * @return Cell The start point of the labyrinth.
     */
    Cell getStartPoint();

    /**
     * @brief Retrieves the width of the labyrinth.
     * 
     * @return unsigned int The width of the labyrinth.
     */
    unsigned int getWidth();
    
    /**
     * @brief Retrieves the height of the labyrinth.
     * 
     * @return unsigned int The height of the labyrinth.
     */
    unsigned int getHeight();

    /**
     * @brief Sets the value of a specific cell in the labyrinth.
     * 
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     * @param cell The Cell object to set at the specified position.
     * 
     * @details 
     * Updates the cell at the given row and column with the provided Cell object.
     */
    void setCell(unsigned int row, unsigned int col, const Cell& cell);
    
    /**
     * @brief Retrieves a reference to a specific cell in the labyrinth.
     * 
     * @param row The row index of the cell.
     * @param col The column index of the cell.
     * 
     * @return Cell& Reference to the specified cell.
     */
    Cell& getCell(unsigned int row, unsigned int col) const;

    /**
     * @brief Checks if the labyrinth map was generated successfully.
     * 
     * @return bool True if generation was successful, false otherwise.
     */
    bool getMapGenerationSuccess();

    /**
     * @brief Sets quiet mode to suppress debug output during tests.
     * 
     * @param quiet If true, disables debug output; if false, enables it.
     */
    void setQuietMode(bool quiet);

    /**
     * @brief Retrieves the time taken to generate the labyrinth.
     * 
     * @return uint64_t The generation time in milliseconds.
     */
    uint64_t getGenerationTime() const;

    /**
     * @brief Retrieves the path from the entrance to the exit.
     * 
     * @return std::list<Cell*> The list of cells forming the path.
     */
    std::list<Cell*> getPathFromEntranceToExit();
};

#endif // LABYRINTH_H