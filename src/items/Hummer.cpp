
#include "items/Hummer.h"
#include "Player.h"

Hummer::~Hummer()
{
}

void Hummer::applyEffect(Player& player)
{
	player.addHummerEffect();
}

void Hummer::removeEffect(Player& player)
{
	player.removeHummerEffect();
}