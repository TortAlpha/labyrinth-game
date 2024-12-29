
#ifndef SHIELD_H
#define SHIELD_H

#include "Item.h"
#include "Cell.h"

class Shield : public Item
{
	private:	

	public:
		void applyEffect() override;
		void removeEffect() override;
		Shield(Cell pos, int effectDuration = 3) : Item(pos, effectDuration) {};
		~Shield();
};

#endif // SHIELD_H
