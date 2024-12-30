#ifndef SHIELD_H
#define SHIELD_H

#include "Item.h"
#include "Cell.h"

/**
 * @brief Represents the Shield item within the labyrinth.
 * 
 * @details 
 * The Shield class inherits from the abstract Item class and implements the specific
 * behavior for the Shield effect. When activated, this effect provides the player with
 * temporary protection, reducing or nullifying damage from enemy attacks, such as those from the minotaur.
 * 
 * Author: Roman Avanesov
 * Created: 25.12.2024
 * Last Modified: 30.12.2024
 */
class Shield : public Item
{
    private:	

    public:
        /**
         * @brief Applies the Shield effect to the player.
         * 
         * @param player Reference to the Player object to which the effect is applied.
         * 
         * @details 
         * Activates the Shield effect by invoking the player's `addShieldEffect` method.
         * This effect typically provides the player with temporary protection, reducing or nullifying
         * damage from enemy attacks, such as those from the minotaur.
         */
        void applyEffect(Player& player) override;

        /**
         * @brief Removes the Shield effect from the player.
         * 
         * @param player Reference to the Player object from which the effect is removed.
         * 
         * @details 
         * Deactivates the Shield effect by invoking the player's `removeShieldEffect` method.
         * This removes the temporary protection, returning the player to their normal state of vulnerability.
         */
        void removeEffect(Player& player) override;

        /**
         * @brief Constructs a Shield item with a specified position and effect duration.
         * 
         * @param pos The Cell object representing the item's position within the labyrinth.
         * @param effectDuration The duration for which the item's effect remains active. Defaults to 3.
         * 
         * @details 
         * Initializes the Shield item by calling the base Item class constructor with the given
         * position and effect duration. Sets the `takeMessage`, `removeMessage`, and `infoMessage`
         * to provide feedback to the player when interacting with the item.
         */
        Shield(Cell pos, int effectDuration = 3) 
            : Item(pos, effectDuration) 
        { 
            takeMessage = "Shield effect applied."; 
            removeMessage = "Shield effect removed."; 
            infoMessage = "Shield effect active."; 
        };

        /**
         * @brief Destructor for the Shield class.
         * 
         * @details 
         * Currently does not perform any specific actions as there are no dynamically allocated resources.
         * This destructor is declared as `override` to ensure proper cleanup in case the base class destructor
         * becomes virtual in the future.
         */
        ~Shield() override;
};

#endif // SHIELD_H