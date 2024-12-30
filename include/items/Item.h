
#ifndef ITEM_H
#define ITEM_H

#include "Cell.h"
#include "Player.h"
#include <iostream>
#include <string>

class Item
{
	protected:

		Cell position;
		int effectDuration;
		bool active;
		bool used;
		std::string takeMessage;
		std::string removeMessage;
		std::string infoMessage;

	public:

		virtual void applyEffect(Player& player) = 0;
		virtual void removeEffect(Player& player) = 0;
		
		void activate();
		void deactivate();
		
		bool isUsed();
		void setUsed();

		void setEffectDuration(int effectDuration);
		void setPosition(Cell position);

		Cell getPosition() const;
		bool isActive() const;
		int getEffectDuration() const;

		void printInfoMessage();
		void printTakeMessage();
		void printRemoveMessage();

		Item(Cell position, int effectDuration = 3) : position(position), effectDuration(effectDuration), active(false), used(false) {};
		Item(int row, int col, int effectDuration = 3) : position(row, col, 'P'), effectDuration(effectDuration), active(false), used(false) {};
		
		virtual ~Item();

};

#endif // ITEM_H