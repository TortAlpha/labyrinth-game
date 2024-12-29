
#include "Minotaur.h"


Minotaur::~Minotaur()
{
}

Cell Minotaur::getPosition()
{
	return this->position;
}

void Minotaur::setPosition(Cell position)
{
	this->position = position;
}