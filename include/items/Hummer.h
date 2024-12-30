#ifndef HUMMER_H
#define HUMMER_H

#include "Item.h"
#include "Cell.h"
#include "Player.h"

/**
 * @brief Represents the Hummer item within the labyrinth.
 * 
 * @details 
 * The Hummer class inherits from the abstract Item class and implements the specific
 * behavior for the Hummer effect. When activated, this effect allows the player to
 * destroy walls or obstacles within the labyrinth, enhancing mobility and access to
 * previously inaccessible areas.
 * 
 * Author: Roman Avanesov
 * Created: 25.12.2024
 * Last Modified: 30.12.2024
 */
class Hummer : public Item
{
    private:

    public:
        /**
         * @brief Applies the Hummer effect to the player.
         * 
         * @param player Reference to the Player object to which the effect is applied.
         * 
         * @details 
         * Activates the Hummer effect by invoking the player's `addHummerEffect` method.
         * This effect typically allows the player to destroy walls or obstacles within the labyrinth,
         * enhancing mobility and access to new areas.
         */
        void applyEffect(Player& player) override;

        /**
         * @brief Removes the Hummer effect from the player.
         * 
         * @param player Reference to the Player object from which the effect is removed.
         * 
         * @details 
         * Deactivates the Hummer effect by invoking the player's `removeHummerEffect` method.
         * This removes the player's ability to destroy walls or obstacles, reverting their abilities
         * to the normal state.
         */
        void removeEffect(Player& player) override;

        /**
         * @brief Constructs a Hummer item with a specified position and effect duration.
         * 
         * @param pos The Cell object representing the item's position within the labyrinth.
         * @param effectDuration The duration for which the item's effect remains active. Defaults to 3.
         * 
         * @details 
         * Initializes the Hummer item by calling the base Item class constructor with the given
         * position and effect duration. Sets the `takeMessage`, `removeMessage`, and `infoMessage`
         * to provide feedback to the player when interacting with the item.
         */
        Hummer(Cell pos, int effectDuration = 3) 
            : Item(pos, effectDuration) 
        { 
            takeMessage = "Hummer effect applied."; 
            removeMessage = "Hummer effect removed."; 
            infoMessage = "Hummer effect active."; 
        };

        /**
         * @brief Destructor for the Hummer class.
         * 
         * @details 
         * Currently does not perform any specific actions as there are no dynamically allocated resources.
         * This destructor is declared as `override` to ensure proper cleanup in case the base class destructor
         * becomes virtual in the future.
         */
        ~Hummer() override;
};

#endif // HUMMER_H