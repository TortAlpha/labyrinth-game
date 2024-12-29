
#include "items/Shield.h"

Shield::~Shield()
{
}

void Shield::applyEffect(Player& player)
{
	player.addShieldEffect();
}

void Shield::removeEffect(Player& player)
{
	player.removeShieldEffect();
}
