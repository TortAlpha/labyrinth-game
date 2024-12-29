
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

void Player::addSwordEffect()
{
	this->swordEffect = true;
}

void Player::removeSwordEffect()
{
	this->swordEffect = false;
}

void Player::addShieldEffect()
{
	this->shieldEffect = true;
}

void Player::removeShieldEffect()
{
	this->shieldEffect = false;
}

void Player::addHummerEffect()
{
	this->hummerEffect = true;
}

void Player::removeHummerEffect()
{
	this->hummerEffect = false;
}

void Player::addFogOfWarEffect()
{
	this->fogOfWarEffect = true;
}

void Player::removeFogOfWarEffect()
{
	this->fogOfWarEffect = false;
}