
#ifndef MINOTAUR_H
#define MINOTAUR_H

#include "Cell.h"

class Minotaur {

	private:
			
		Cell position;

	public:

		Minotaur(/* args */);
		~Minotaur();

		Cell getPosition();
		void setPosition(Cell position);

};

#endif // MINOTAUR_H