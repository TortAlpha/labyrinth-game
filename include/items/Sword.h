
#ifndef SWORD_H
#define SWORD_H

#include "Item.h"

class Sword : public Item
{
	private:

	public:
		void applyEffect() override;	
		void removeEffect() override;
		Sword(int row, int col, int effectDuration = 3) : Item(row, col, effectDuration) {};
		~Sword();		
};

#endif // SWORD_H