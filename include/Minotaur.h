
#ifndef MINOTAUR_H
#define MINOTAUR_H

#include "Cell.h"

class Minotaur {

	private:
			
		Cell position;
		bool alive;

	public:

		Minotaur(/* args */) : alive(true) {};
		~Minotaur();

		bool isAlive() { return alive; };
		void kill() { alive = false; }

		Cell getPosition();
		void setPosition(Cell position);

};

#endif // MINOTAUR_H