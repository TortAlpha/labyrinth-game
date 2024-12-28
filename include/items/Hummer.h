
#ifndef HUMMER_H
#define HUMMER_H

#include "Item.h"

class Hummer : public Item
{
	private:

	public:
		void applyEffect() override;
		void removeEffect() override;
		Hummer(int row, int col, int effectDuration = 3) : Item(row, col, effectDuration) {};
		~Hummer();
};

#endif // HUMMER_H