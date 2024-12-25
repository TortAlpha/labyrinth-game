#include "Game.h"
#include "Labyrinth.h"

Game::Game(unsigned int width, unsigned int height)
{
	this->labyrinth = new Labyrinth(width, height);	
}

Game::~Game()
{
	delete this->labyrinth;
}