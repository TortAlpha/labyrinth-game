#ifndef GAME_H
#define GAME_H

#include "Labyrinth.h"

class Game
{
private:
	Labyrinth* labyrinth;
public:
	Game(unsigned int width, unsigned int height);
	~Game();
};

#endif // GAME_H