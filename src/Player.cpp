
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

Cell Player::getPosition()
{
	return this->position;
}

void Player::setPosition(Cell position)
{
	this->position = position;
}