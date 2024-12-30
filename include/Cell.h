#ifndef CELL_H
#define CELL_H

#include <iostream>

/**
 * @brief Represents a single cell within the labyrinth grid.
 * 
 * @details 
 * The Cell class encapsulates the position and value of a cell in the labyrinth.
 * Each cell has a row and column index to denote its position and a character value
 * that represents its state (e.g., wall, player, minotaur, or item).
 * 
 * Author: Roman Avanesov
 * Created: 25.12.2024
 * Last Modified: 30.12.2024
 */
class Cell
{
    private:

        int row;    ///< The row index of the cell within the labyrinth.
        int col;    ///< The column index of the cell within the labyrinth.
        char val;   ///< The character value representing the cell's content.

    public:

        /**
         * @brief Default constructor for the Cell class.
         * 
         * @details 
         * Initializes the cell with default values:
         * - `row` and `col` are set to -1, indicating an undefined position.
         * - `val` is set to '0', representing an uninitialized cell.
         */
        Cell();

        /**
         * @brief Destructor for the Cell class.
         * 
         * @details 
         * Currently does not perform any specific actions as there are no dynamically allocated resources.
         */
        ~Cell();

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
        Cell(int row, int col, char val);
        
        /**
         * @brief Retrieves the row index of the cell.
         * 
         * @return int The row index of the cell.
         */
        int getRow() const;

        /**
         * @brief Retrieves the column index of the cell.
         * 
         * @return int The column index of the cell.
         */
        int getCol() const;

        /**
         * @brief Retrieves the value of the cell.
         * 
         * @return char The character representing the cell's content.
         */
        char getVal() const;

        /**
         * @brief Sets the value of the cell.
         * 
         * @param val The new character value to assign to the cell.
         * 
         * @details 
         * Updates the cell's value to represent different entities or states within the labyrinth,
         * such as walls ('#'), player ('R'), minotaur ('M'), or items ('P').
         */
        void setVal(char val);

        /**
         * @brief Sets the row index of the cell.
         * 
         * @param row The new row index to assign to the cell.
         * 
         * @details 
         * Updates the cell's row position within the labyrinth grid.
         */
        void setRow(int row);

        /**
         * @brief Sets the column index of the cell.
         * 
         * @param col The new column index to assign to the cell.
         * 
         * @details 
         * Updates the cell's column position within the labyrinth grid.
         */
        void setCol(int col);

        /**
         * @brief Assignment operator for the Cell class.
         * 
         * @param other The Cell object to assign from.
         * @return Cell& Reference to the current Cell object after assignment.
         * 
         * @details 
         * Copies the row, column, and value from the `other` Cell to the current Cell.
         */
        Cell& operator=(const Cell& other);

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
        bool operator==(const Cell& other) const;

        /**
         * @brief Overloads the stream insertion operator to output the cell's value.
         * 
         * @param os The output stream.
         * @param cell The Cell object to output.
         * @return std::ostream& Reference to the output stream.
         * 
         * @details 
         * Allows the cell's value to be easily printed to output streams, such as `std::cout`.
         */
        friend std::ostream& operator<<(std::ostream& os, const Cell& cell) {
            os << cell.val;
            return os;
        };
};

#endif // CELL_H