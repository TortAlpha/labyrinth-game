#ifndef FOGOFWAR_H
#define FOGOFWAR_H

#include "Item.h"
#include "Cell.h"

/**
 * @brief Represents the Fog of War item within the labyrinth.
 * 
 * @details 
 * The FogOfWar class inherits from the abstract Item class and implements the specific
 * behavior for the Fog of War effect. When activated, this effect limits the player's
 * visibility within the labyrinth, typically restricting it to a certain radius around
 * the player's current position.
 * 
 * Author: Roman Avanesov
 * Created: 25.12.2024
 * Last Modified: 30.12.2024
 */
class FogOfWar : public Item
{
    private:

    public:
        /**
         * @brief Applies the Fog of War effect to the player.
         * 
         * @param player Reference to the Player object to which the effect is applied.
         * 
         * @details 
         * Activates the Fog of War effect by invoking the player's `addFogOfWarEffect` method.
         * This effect typically restricts the player's visibility within the labyrinth, enhancing
         * the game's challenge by limiting the player's awareness of their surroundings.
         */
        void applyEffect(Player& player) override;

        /**
         * @brief Removes the Fog of War effect from the player.
         * 
         * @param player Reference to the Player object from which the effect is removed.
         * 
         * @details 
         * Deactivates the Fog of War effect by invoking the player's `removeFogOfWarEffect` method.
         * This restores the player's full visibility within the labyrinth, removing any restrictions
         * imposed by the effect.
         */
        void removeEffect(Player& player) override;

        /**
         * @brief Constructs a FogOfWar item with a specified position and effect duration.
         * 
         * @param pos The Cell object representing the item's position within the labyrinth.
         * @param effectDuration The duration for which the item's effect remains active. Defaults to 3.
         * 
         * @details 
         * Initializes the FogOfWar item by calling the base Item class constructor with the given
         * position and effect duration. Sets the `takeMessage`, `removeMessage`, and `infoMessage`
         * to provide feedback to the player when interacting with the item.
         */
        FogOfWar(Cell pos, int effectDuration = 3) 
            : Item(pos, effectDuration) 
        { 
            takeMessage = "Fog of War effect applied."; 
            removeMessage = "Fog of War effect removed."; 
            infoMessage = "Fog of War effect active."; 
        };

        /**
         * @brief Destructor for the FogOfWar class.
         * 
         * @details 
         * Currently does not perform any specific actions as there are no dynamically allocated resources.
         * This destructor is declared as `override` to ensure proper cleanup in case the base class destructor
         * becomes virtual in the future.
         */
        ~FogOfWar() override;
};

#endif // FOGOFWAR_H