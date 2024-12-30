#ifndef FOGOFWAR_H
#define FOGOFWAR_H

#include "Item.h"
#include "Cell.h"

class FogOfWar : public Item
{
	private:

	public:
		void applyEffect(Player& player) override;
		void removeEffect(Player& player) override;
		FogOfWar(Cell pos, int effectDuration = 3) : Item(pos, effectDuration) { takeMessage = "Fog of War effect applied."; removeMessage = "Fog of War effect removed."; infoMessage = "Fog of War effect active."; };
		~FogOfWar() override;
};

#endif // FOGOFWAR_H
