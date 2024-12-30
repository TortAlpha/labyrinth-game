#ifndef SWORD_H
#define SWORD_H

#include "Item.h"
#include "Cell.h"

/**
 * @brief Represents the Sword item within the labyrinth.
 * 
 * @details 
 * The Sword class inherits from the abstract Item class and implements the specific
 * behavior for the Sword effect. When activated, this effect enhances the player's
 * ability to attack enemies within a certain range, providing increased damage or
 * attack capabilities against adversaries like the minotaur.
 * 
 * Author: Roman Avanesov
 * Created: 25.12.2024
 * Last Modified: 30.12.2024
 */
class Sword : public Item
{
    private:

    public:
        /**
         * @brief Applies the Sword effect to the player.
         * 
         * @param player Reference to the Player object to which the effect is applied.
         * 
         * @details 
         * Activates the Sword effect by invoking the player's `addSwordEffect` method.
         * This effect typically increases the player's attack damage or range, allowing for
         * more effective combat against enemies such as the minotaur.
         */
        void applyEffect(Player& player) override;    

        /**
         * @brief Removes the Sword effect from the player.
         * 
         * @param player Reference to the Player object from which the effect is removed.
         * 
         * @details 
         * Deactivates the Sword effect by invoking the player's `removeSwordEffect` method.
         * This removes the enhanced attack capabilities, reverting the player to their normal
         * attack state.
         */
        void removeEffect(Player& player) override;

        /**
         * @brief Constructs a Sword item with a specified position and effect duration.
         * 
         * @param pos The Cell object representing the item's position within the labyrinth.
         * @param effectDuration The duration for which the item's effect remains active. Defaults to 3.
         * 
         * @details 
         * Initializes the Sword item by calling the base Item class constructor with the given
         * position and effect duration. Sets the `takeMessage`, `removeMessage`, and `infoMessage`
         * to provide feedback to the player when interacting with the item.
         */
        Sword(Cell pos, int effectDuration = 3) 
            : Item(pos, effectDuration) 
        { 
            takeMessage = "Sword effect applied."; 
            removeMessage = "Sword effect removed."; 
            infoMessage = "Sword effect active."; 
        };

        /**
         * @brief Destructor for the Sword class.
         * 
         * @details 
         * Currently does not perform any specific actions as there are no dynamically allocated resources.
         * This destructor is declared as `override` to ensure proper cleanup in case the base class destructor
         * becomes virtual in the future.
         */
        ~Sword() override;        
};

#endif // SWORD_H