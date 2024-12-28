
#ifndef ITEM_H
#define ITEM_H

#include "Cell.h"

class Item
{
	protected:

		Cell position;
		int effectDuration;
		bool active;

	public:

		virtual void applyEffect() = 0;
		virtual void removeEffect() = 0;
		
		void activate();
		
		void setEffectDuration(int effectDuration);
		void setPosition(Cell position);

		Cell getPosition() const;
		bool isActive() const;
		int getEffectDuration() const;

		Item(Cell position, int effectDuration = 3) : position(position), effectDuration(effectDuration), active(false) {};
		Item(int row, int col, int effectDuration = 3) : position(row, col, 'P'), effectDuration(effectDuration), active(false) {};
		~Item();

};

#endif // ITEM_H