#include "Game.h"

int main(void) {

    unsigned int width, height;
    std::cout << "Enter width of labyrinth: ";
    std::cin >> width;
    std::cout << "Enter height of labyrinth: ";
    std::cin >> height;
    
    if (width < 15 && height < 15) {
        std::cout << "Width and height must be at least 15.\n";
        return 1;
    }

    Game* game = new Game(width, height);

    return 0;
}