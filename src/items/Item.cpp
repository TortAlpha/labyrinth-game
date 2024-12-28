
#include "items/Item.h"

Item::~Item()
{
}

void Item::activate()
{
	active = true;
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

bool Item::isActive() const
{
	return active;
}

int Item::getEffectDuration() const
{
	return effectDuration;
}