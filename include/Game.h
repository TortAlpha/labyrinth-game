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
	int numItems;

	// Logger object to log game events
	Logger logger;

	// Enumeration to represent the game state
	enum GAME_STATE {
		PLAYING,
		PLAYER_WON,
		PLAYER_LOST,
		QUIT
	};

	GAME_STATE state;

	// Game initialization methods
	void init(unsigned int width, unsigned int height);
	void spawn();

	// Helper methods
	bool isWall(const Cell& position) const;
	bool isMapBorder(const Cell& position) const;

	// Game logic methods
	void checkGameObjectCollision();
	void playerMovementUpdate(char command);
	void minotaurMovementUpdate();
	void itemsEffectUpdate();
	void attackMinotaur();

	//Print methods
	void printMap();
	void printGameOver();
	void printGameWon();

public:
	Game(unsigned int width, unsigned int height, unsigned int numItems);
	~Game();

	// Main game loop
	void updateGameState();
};

#endif // GAME_H