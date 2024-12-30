//
// Creator: Roman Avanesov
// Date of creation: 25.12.2024
// Date of last update: 30.12.2024
// Description: This is the main file of the game. It initializes and starts the game.
// Git repository: https://github.com/TortAlpha/labyrinth-game
//

#include "Game.h"
#include <iostream>

/**
 * @brief The main entry point of the Labyrinth Robot game.
 * 
 * @details 
 * This function prompts the user to input the dimensions of the labyrinth and the number of special items.
 * It validates the input and initializes the Game object, which starts the game.
 * 
 * @return int Returns 0 if the game initializes successfully, otherwise returns 1.
 */
int main() {
    unsigned int width, height, numItems;

    // Prompt the user for labyrinth dimensions and number of items
    std::cout << "Enter width of labyrinth: ";
    std::cin >> width;
    std::cout << "Enter height of labyrinth: ";
    std::cin >> height;
    std::cout << "Enter number of items: ";
    std::cin >> numItems;

    // Validate the labyrinth dimensions
    if (width < 15 || height < 15) {
        std::cout << "Width and height must be at least 15.\n";
        return 1; // Exit with error code
    }

    // Validate the number of items
    if (numItems < 4) {
        std::cout << "Number of items must be at least 4.\n";
        return 1; // Exit with error code
    }

    /**
     * @brief Initialize and start the game.
     * 
     * @details 
     * Creates a Game object with the specified dimensions and number of items.
     * The Game constructor handles the game loop and gameplay mechanics.
     */
    Game game(width, height, numItems);

    return 0; // Exit successfully
}