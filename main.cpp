#include "Game.h"

int main(void) {

    unsigned int width, height, numItems;
    std::cout << "Enter width of labyrinth: ";
    std::cin >> width;
    std::cout << "Enter height of labyrinth: ";
    std::cin >> height;
    std::cout << "Enter number of items: ";
    std::cin >> numItems;
    
    if (width < 15 || height < 15) {
        std::cout << "Width and height must be at least 15.\n";
        return 1;
    }

    if (numItems < 4) {
        std::cout << "Number of items must be at least 4.\n";
        return 1;
    }

    Game* game = new Game(width, height, numItems);

    return 0;
}