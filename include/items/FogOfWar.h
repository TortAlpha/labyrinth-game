
#ifndef FOGOFWAR_H
#define FOGOFWAR_H

#include "Item.h"
#include "Cell.h"

class FogOfWar : public Item
{
	private:

	public:
		void applyEffect() override;
		void removeEffect() override;
		FogOfWar(Cell pos, int effectDuration = 3) : Item(pos, effectDuration) {};
		~FogOfWar();
};

#endif // FOGOFWAR_H
