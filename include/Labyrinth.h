#ifndef LABYRINTH_H
#define LABYRINTH_H

#include "Cell.h"

class Labyrinth
{
private:
	unsigned int width;
	unsigned int height;
	Cell** labyrinth;

    void createSemicircle(unsigned int centerRow, unsigned int centerCol,
                          unsigned int radius, bool topHalf);
    bool isPathExists(unsigned int sr, unsigned int sc,
                      unsigned int er, unsigned int ec);
	bool wallCondition();

public:

	Labyrinth(/* args */);
	Labyrinth(unsigned int width, unsigned int height);
	~Labyrinth();
	void generate();
	void print();

	void setCell(unsigned int row, unsigned int col, const Cell& cell);
	Cell& getCell(unsigned int row, unsigned int col);

};

#endif // LABYRINTH_H