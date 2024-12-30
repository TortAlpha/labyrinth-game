#include "Cell.h"

/**
 * @brief Default constructor for the Cell class.
 * 
 * @details 
 * Initializes the cell with default values:
 * - `row` and `col` are set to -1, indicating an undefined position.
 * - `val` is set to '0', representing an uninitialized cell.
 */
Cell::Cell()
{
    this->row = -1;
    this->col = -1;
    this->val = '0';
}

/**
 * @brief Destructor for the Cell class.
 * 
 * @details 
 * Currently does not perform any specific actions as there are no dynamically allocated resources.
 */
Cell::~Cell()
{
}

/**
 * @brief Parameterized constructor for the Cell class.
 * 
 * @param row The row index of the cell within the labyrinth.
 * @param col The column index of the cell within the labyrinth.
 * @param val The character value representing the cell's content (e.g., wall, player).
 * 
 * @details 
 * Initializes the cell with the specified row, column, and value.
 */
Cell::Cell(int row, int col, char val)
{
    this->row = row;
    this->col = col;
    this->val = val;
}

/**
 * @brief Retrieves the row index of the cell.
 * 
 * @return int The row index of the cell.
 */
int Cell::getRow() const
{
    return this->row;
}

/**
 * @brief Retrieves the column index of the cell.
 * 
 * @return int The column index of the cell.
 */
int Cell::getCol() const
{
    return this->col;
}

/**
 * @brief Retrieves the value of the cell.
 * 
 * @return char The character representing the cell's content.
 */
char Cell::getVal() const
{
    return this->val;
}

/**
 * @brief Sets the value of the cell.
 * 
 * @param val The new character value to assign to the cell.
 * 
 * @details 
 * Updates the cell's value to represent different entities or states within the labyrinth,
 * such as walls ('#'), player ('R'), minotaur ('M'), or items ('P').
 */
void Cell::setVal(char val)
{
    this->val = val;
}

/**
 * @brief Assignment operator for the Cell class.
 * 
 * @param other The Cell object to assign from.
 * @return Cell& Reference to the current Cell object after assignment.
 * 
 * @details 
 * Copies the row, column, and value from the `other` Cell to the current Cell.
 */
Cell& Cell::operator=(const Cell& other)
{
    this->row = other.row;
    this->col = other.col;
    this->val = other.val;
    return *this;
}

/**
 * @brief Sets the row index of the cell.
 * 
 * @param row The new row index to assign to the cell.
 * 
 * @details 
 * Updates the cell's row position within the labyrinth grid.
 */
void Cell::setRow(int row)
{
    this->row = row;
}

/**
 * @brief Sets the column index of the cell.
 * 
 * @param col The new column index to assign to the cell.
 * 
 * @details 
 * Updates the cell's column position within the labyrinth grid.
 */
void Cell::setCol(int col)
{
    this->col = col;
}

/**
 * @brief Equality operator for the Cell class.
 * 
 * @param other The Cell object to compare with.
 * @return true If both cells have the same row and column indices.
 * @return false Otherwise.
 * 
 * @details 
 * Determines if two cells occupy the same position within the labyrinth by comparing
 * their row and column indices. The cell's value (`val`) is not considered in this comparison.
 */
bool Cell::operator==(const Cell& other) const
{
    return this->row == other.row && this->col == other.col;
}