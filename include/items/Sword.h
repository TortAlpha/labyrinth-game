
#ifndef SWORD_H
#define SWORD_H

#include "Item.h"
#include "Cell.h"

class Sword : public Item
{
	private:

	public:
		void applyEffect() override;	
		void removeEffect() override;
		Sword(Cell pos, int effectDuration = 3) : Item(pos, effectDuration) {};
		~Sword();		
};

#endif // SWORD_H