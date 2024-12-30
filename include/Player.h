#ifndef PLAYER_H
#define PLAYER_H

#include "Cell.h"

// Forward declaration to avoid circular dependency
class Item;

/**
 * @brief The Player class represents the robot navigating through the labyrinth.
 * 
 * @details 
 * Manages the player's position, active effects, and immunity status.
 * Provides methods to apply and remove various effects obtained from items.
 * 
 * Author: Roman Avanesov
 * Created: 25.12.2024
 * Last Modified: 30.12.2024
 */
class Player {

    private:

        Cell position;                  ///< The current position of the player in the labyrinth.
        
        // Special effects flags
        bool swordEffect = false;       ///< Indicates if the sword effect is active.
        bool shieldEffect = false;      ///< Indicates if the shield effect is active.
        bool hummerEffect = false;      ///< Indicates if the hummer effect is active.
        bool fogOfWarEffect = false;    ///< Indicates if the fog of war effect is active.

        // Immunity status
        bool immuneToMinotaur = false;  ///< Indicates if the player is currently immune to the Minotaur.
        int immuneDuration = 0;          ///< Duration of immunity in turns.

    public:
    
        /**
         * @brief Default constructor for the Player class.
         * 
         * @details Initializes the player's position and sets all effect flags to false.
         */
        Player();

        /**
         * @brief Destructor for the Player class.
         * 
         * @details Currently does not perform any specific actions.
         */
        ~Player();

        /**
         * @brief Retrieves the current position of the player.
         * 
         * @return Cell The current position of the player.
         */
        Cell getPosition() const;

        /**
         * @brief Sets the player's position in the labyrinth.
         * 
         * @param position The new position to set for the player.
         */
        void setPosition(const Cell& position);

        /**
         * @brief Activates the sword effect for the player.
         * 
         * @details Grants the ability to destroy the Minotaur.
         */
        void addSwordEffect();

        /**
         * @brief Deactivates the sword effect for the player.
         * 
         * @details Removes the ability to destroy the Minotaur.
         */
        void removeSwordEffect();

        /**
         * @brief Activates the shield effect for the player.
         * 
         * @details Grants the ability to defend against the Minotaur.
         */
        void addShieldEffect();

        /**
         * @brief Deactivates the shield effect for the player.
         * 
         * @details Removes the ability to defend against the Minotaur.
         */
        void removeShieldEffect();

        /**
         * @brief Activates the hummer effect for the player.
         * 
         * @details Grants the ability to pass through walls.
         */
        void addHummerEffect();

        /**
         * @brief Deactivates the hummer effect for the player.
         * 
         * @details Removes the ability to pass through walls.
         */
        void removeHummerEffect();

        /**
         * @brief Activates the fog of war effect for the player.
         * 
         * @details Reduces the player's visibility to a 3x3 submatrix.
         */
        void addFogOfWarEffect();

        /**
         * @brief Deactivates the fog of war effect for the player.
         * 
         * @details Restores the player's full visibility in the labyrinth.
         */
        void removeFogOfWarEffect();

        /**
         * @brief Sets the player's immunity status against the Minotaur.
         * 
         * @param immune Boolean indicating whether to grant immunity.
         * @param immuneDuration Duration of immunity in turns.
         */
        void setImmuneToMinotaur(bool immune, int immuneDuration) {
            immuneToMinotaur = immune;
            this->immuneDuration = immuneDuration;
        }

        /**
         * @brief Checks if the player is currently immune to the Minotaur.
         * 
         * @return true If the player is immune.
         * @return false Otherwise.
         */
        bool isImmuneToMinotaur() const { return immuneToMinotaur; }

        /**
         * @brief Retrieves the remaining duration of the player's immunity.
         * 
         * @return int Remaining immunity duration in turns.
         */
        int getImmuneDuration() const { return immuneDuration; }

        /**
         * @brief Decreases the player's immunity duration by one turn.
         * 
         * @details If the immunity duration reaches zero, the player is no longer immune.
         */
        void decreaseImmuneDuration() { 
            immuneDuration--; 
            if (immuneDuration <= 0) {
                immuneToMinotaur = false; 
                immuneDuration = 0; // Prevent negative duration
            } 
        }

        /**
         * @brief Checks if the sword effect is active.
         * 
         * @return true If the sword effect is active.
         * @return false Otherwise.
         */
        bool hasSwordEffect() const { return swordEffect; }

        /**
         * @brief Checks if the shield effect is active.
         * 
         * @return true If the shield effect is active.
         * @return false Otherwise.
         */
        bool hasShieldEffect() const { return shieldEffect; }

        /**
         * @brief Checks if the hummer effect is active.
         * 
         * @return true If the hummer effect is active.
         * @return false Otherwise.
         */
        bool hasHummerEffect() const { return hummerEffect; }

        /**
         * @brief Checks if the fog of war effect is active.
         * 
         * @return true If the fog of war effect is active.
         * @return false Otherwise.
         */
        bool hasFogOfWarEffect() const { return fogOfWarEffect; }
};

#endif // PLAYER_H