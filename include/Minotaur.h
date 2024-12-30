#ifndef MINOTAUR_H
#define MINOTAUR_H

#include "Cell.h"

/**
 * @brief The Minotaur class represents the mythical creature navigating through the labyrinth.
 * 
 * @details 
 * Manages the Minotaur's position and alive status. Provides methods to retrieve and
 * update the Minotaur's position, check if it is alive, and to kill it.
 * 
 * Author: Roman Avanesov
 * Created: 25.12.2024
 * Last Modified: 30.12.2024
 */
class Minotaur {

    private:
        Cell position;      ///< The current position of the Minotaur in the labyrinth.
        bool alive;         ///< Indicates whether the Minotaur is alive.

    public:

        /**
         * @brief Default constructor for the Minotaur class.
         * 
         * @details Initializes the Minotaur as alive.
         */
        Minotaur() : alive(true) {}

        /**
         * @brief Destructor for the Minotaur class.
         * 
         * @details Currently does not perform any specific actions.
         */
        ~Minotaur();

        /**
         * @brief Checks if the Minotaur is alive.
         * 
         * @return true If the Minotaur is alive.
         * @return false If the Minotaur is dead.
         */
        bool isAlive() const { return alive; }

        /**
         * @brief Kills the Minotaur.
         * 
         * @details Sets the Minotaur's alive status to false.
         */
        void kill() { alive = false; }

        /**
         * @brief Retrieves the current position of the Minotaur.
         * 
         * @return Cell The current position of the Minotaur.
         */
        Cell getPosition() const;

        /**
         * @brief Sets the Minotaur's position in the labyrinth.
         * 
         * @param position The new position to set for the Minotaur.
         */
        void setPosition(const Cell& position);
};

#endif // MINOTAUR_H