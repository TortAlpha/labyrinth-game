
#include "Cell.h"

Cell::Cell()
{
	this->row = -1;
	this->col = -1;
	this->val = '0';
}

Cell::~Cell()
{
}

Cell::Cell(int row, int col, char val)
{
	this->row = row;
	this->col = col;
	this->val = val;
}

int Cell::getRow()
{
	return this->row;
}

int Cell::getCol()
{
	return this->col;
}

char Cell::getVal()
{
	return this->val;
}

void Cell::setVal(char val)
{
	this->val = val;
}

Cell& Cell::operator=(const Cell& other)
{
	this->row = other.row;
	this->col = other.col;
	this->val = other.val;
	return *this;
}

