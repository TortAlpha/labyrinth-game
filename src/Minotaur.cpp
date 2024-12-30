#include "Minotaur.h"

/**
 * @brief Destructor for the Minotaur class.
 * 
 * @details Currently does not perform any specific actions.
 */
Minotaur::~Minotaur()
{
    // No additional cleanup required
}

/**
 * @brief Retrieves the current position of the Minotaur.
 * 
 * @return Cell The current position of the Minotaur.
 */
Cell Minotaur::getPosition() const
{
    return this->position;
}

/**
 * @brief Sets the Minotaur's position in the labyrinth.
 * 
 * @param position The new position to set for the Minotaur.
 */
void Minotaur::setPosition(const Cell& position)
{
    this->position = position;
}