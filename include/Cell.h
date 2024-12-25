
#ifndef CELL_H
#define CELL_H

#include <iostream>

class Cell
{
	private:

		int row;
		int col;
		char val;

	public:

		Cell();
		~Cell();
		Cell(int row, int col, char val);
		
		int getRow();
		int getCol();
		char getVal();
		void setVal(char val);

		Cell& operator=(const Cell& other);

		friend std::ostream& operator<<(std::ostream& os, const Cell& cell) {
        	os << cell.val;
			return os;
    	};
};

#endif // CELL_H