
#ifndef SHIELD_H
#define SHIELD_H

#include "Item.h"

class Shield : public Item
{
	private:	

	public:
		void applyEffect() override;
		void removeEffect() override;
		Shield(int row, int col, int effectDuration = 3) : Item(row, col, effectDuration) {};
		~Shield();
};

#endif // SHIELD_H
