
#ifndef SHIELD_H
#define SHIELD_H

#include "Item.h"
#include "Cell.h"

class Shield : public Item
{
	private:	

	public:
		void applyEffect(Player& player) override;
		void removeEffect(Player& player) override;
		Shield(Cell pos, int effectDuration = 3) : Item(pos, effectDuration) { takeMessage = "Shield effect applied."; removeMessage = "Shield effect removed."; infoMessage = "Shield effect active."; };
		~Shield() override;
};

#endif // SHIELD_H
