
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
		
		int getRow() const;
		int getCol() const;
		char getVal() const;
		void setVal(char val);

		void setRow(int row);
		void setCol(int col);

		Cell& operator=(const Cell& other);

		bool operator==(const Cell& other) const;

		friend std::ostream& operator<<(std::ostream& os, const Cell& cell) {
        	os << cell.val;
			return os;
    	};

};

#endif // CELL_H