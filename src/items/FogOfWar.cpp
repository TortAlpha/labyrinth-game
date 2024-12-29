
#include "items/FogOfWar.h"

FogOfWar::~FogOfWar()
{
}

void FogOfWar::applyEffect(Player& player)
{
	player.addFogOfWarEffect();
}

void FogOfWar::removeEffect(Player& player)
{
	player.removeFogOfWarEffect();
}