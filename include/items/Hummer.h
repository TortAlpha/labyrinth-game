
#ifndef HUMMER_H
#define HUMMER_H

#include "Item.h"
#include "Cell.h"

class Hummer : public Item
{
	private:

	public:
		void applyEffect() override;
		void removeEffect() override;
		Hummer(Cell pos, int effectDuration = 3) : Item(pos, effectDuration) {};
		~Hummer();
};

#endif // HUMMER_H