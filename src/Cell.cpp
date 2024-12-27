
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

int Cell::getRow() const
{
	return this->row;
}

int Cell::getCol() const
{
	return this->col;
}

char Cell::getVal() const
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

void Cell::setRow(int row)
{
	this->row = row;
}

void Cell::setCol(int col)
{
	this->col = col;
}

bool Cell::operator==(const Cell& other) const
{
	return this->row == other.row && this->col == other.col;
}
