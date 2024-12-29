
#include "items/Sword.h"

Sword::~Sword()
{
}

void Sword::applyEffect(Player& player)
{
	player.addSwordEffect();
}

void Sword::removeEffect(Player& player)
{
	player.removeSwordEffect();
}