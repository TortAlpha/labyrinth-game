#ifndef LABYRINTH_H
#define LABYRINTH_H

#include "Cell.h"
#include <list>

class Labyrinth
{
private:
	unsigned int width;
	unsigned int height;

	bool mapGeneratedSuccessfully = false;

	Cell startPoint;
	Cell endPoint;

	Cell** labyrinth;

	std::list<Cell*> pathFromEntranceToExit;
	std::list<Cell*> findPathFromEntranceToExit();

    void createSemicircle(unsigned int centerRow, unsigned int centerCol,
                          unsigned int radius, bool topHalf);
    bool isPathExists(unsigned int sr, unsigned int sc,
                      unsigned int er, unsigned int ec);
	bool wallCondition();

public:

	Labyrinth();
	Labyrinth(unsigned int width, unsigned int height);
	~Labyrinth();
	bool generate();
	void print();

	Cell getEndPoint();
	Cell getStartPoint();

	unsigned int getWidth();
	unsigned int getHeight();

	void setCell(unsigned int row, unsigned int col, const Cell& cell);
	Cell& getCell(unsigned int row, unsigned int col) const;

	bool getMapGenerationSuccess();

	std::list<Cell*> getPathFromEntranceToExit();
};

#endif // LABYRINTH_H