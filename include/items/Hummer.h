
#ifndef HUMMER_H
#define HUMMER_H

#include "Item.h"
#include "Cell.h"
#include "Player.h"

class Hummer : public Item
{
	private:

	public:
		void applyEffect(Player& player) override;
		void removeEffect(Player& player) override;
		Hummer(Cell pos, int effectDuration = 3) : Item(pos, effectDuration) { takeMessage = "Hummer effect applied."; 
		removeMessage = "Hummer effect removed."; 
		infoMessage = "Hummer effect active."; };
		~Hummer() override;
};

#endif // HUMMER_H