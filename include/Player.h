
#ifndef PLAYER_H
#define PLAYER_H

#include "Cell.h"

class Player {

	private:

		Cell position;
		
	public:
	
		Player();
		~Player();

		Cell getPosition();
		void setPosition(Cell position);

};

#endif // PLAYER_H