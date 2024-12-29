
#include "items/Item.h"
#include "termcolor.hpp"

Item::~Item()
{
}

void Item::activate()
{
	active = true;
}

void Item::deactivate()
{
	active = false;
}

void Item::setEffectDuration(int effectDuration)
{
	this->effectDuration = effectDuration;
}

void Item::setPosition(Cell position)
{
	this->position = position;
}

Cell Item::getPosition() const
{
	return position;
}

void Item::setUsed()
{
	used = true;
}

bool Item::isUsed()
{
	return used;
}

bool Item::isActive() const
{
	return active;
}

int Item::getEffectDuration() const
{
	return effectDuration;
}


void Item::printInfoMessage()
{
	std::cout << termcolor::on_yellow << infoMessage << termcolor::reset << std::endl;
}

void Item::printTakeMessage()
{
	std::cout << termcolor::on_yellow << takeMessage << termcolor::reset << std::endl;
}

void Item::printRemoveMessage()
{
	std::cout << termcolor::on_yellow << removeMessage << termcolor::reset << std::endl;
}