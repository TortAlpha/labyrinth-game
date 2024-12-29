
#ifndef SWORD_H
#define SWORD_H

#include "Item.h"
#include "Cell.h"

class Sword : public Item
{
	private:

	public:
		void applyEffect(Player& player) override;	
		void removeEffect(Player& player) override;
		Sword(Cell pos, int effectDuration = 3) : Item(pos, effectDuration) 
		{ takeMessage = "Sword effect applied."; removeMessage = "Sword effect removed."; infoMessage = "Sword effect active."; };
		~Sword();		
};

#endif // SWORD_H