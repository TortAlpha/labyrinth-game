#ifndef GAME_H
#define GAME_H

#include "Labyrinth.h"
#include "Player.h"
#include "Minotaur.h"
#include "Logger.h"
#include "items/Item.h"
#include <list>

class Game
{
private:
	
	Labyrinth* labyrinth;
	Player* player;
	Minotaur* minotaur;
	std::list<Item*> items;

	Logger logger;

	enum GAME_STATE {
		PLAYING,
		PLAYER_WON,
		PLAYER_LOST,
		QUIT
	};

	GAME_STATE state;
	int numItems;

	void init(unsigned int width, unsigned int height);
	void spawn();

	bool isWall(Cell position);

	void checkGameObjectCollision();
	void playerMovementUpdate(char command);
	void minotaurMovementUpdate();
	void itemsEffectUpdate();

	void attackMinotaur();

	void printMap();

	void printGameOver();
	void printGameWon();

public:
	Game(unsigned int width, unsigned int height, unsigned int numItems);
	~Game();

	void updateGameState();
};

#endif // GAME_H