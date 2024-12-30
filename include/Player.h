
#ifndef PLAYER_H
#define PLAYER_H

#include "Cell.h"

class Item;

class Player {

	private:

		Cell position;
		
		bool swordEffect = false;
		bool shieldEffect = false;
		bool hummerEffect = false;
		bool fogOfWarEffect = false;

		bool immuneToMinotaur = false;
		int immuneDuration = 0;

	public:
	
		Player();
		~Player();

		Cell getPosition();
		void setPosition(Cell position);

		void addSwordEffect();
		void removeSwordEffect();

		void addShieldEffect();
		void removeShieldEffect();

		void addHummerEffect();
		void removeHummerEffect();

		void addFogOfWarEffect();
		void removeFogOfWarEffect();

		void setImmuneToMinotaur(bool immune, int immuneDuration) {
			immuneToMinotaur = immune;
			this->immuneDuration = immuneDuration;
		}

		bool isImmuneToMinotaur() const { return immuneToMinotaur; }
		int getImmuneDuration() const { return immuneDuration; }
		void decreaseImmuneDuration() { immuneDuration--; if (immuneDuration == 0) immuneToMinotaur = false; }

		bool hasSwordEffect() const { return swordEffect; }
		bool hasShieldEffect() const { return shieldEffect; }
		bool hasHummerEffect() const { return hummerEffect; }
		bool hasFogOfWarEffect() const { return fogOfWarEffect; }
};

#endif // PLAYER_H