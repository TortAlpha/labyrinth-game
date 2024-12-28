
#ifndef FOGOFWAR_H
#define FOGOFWAR_H

#include "Item.h"

class FogOfWar : public Item
{
	private:

	public:
		void applyEffect() override;
		void removeEffect() override;
		FogOfWar(int row, int col, int effectDuration = 3) : Item(row, col, effectDuration) {};
		~FogOfWar();
};

#endif // FOGOFWAR_H
