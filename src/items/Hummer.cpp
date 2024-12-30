#include "items/Hummer.h"
#include "Player.h"

/**
 * @brief Destructor for the Hummer class.
 * 
 * @details 
 * Currently does not perform any specific actions as there are no dynamically allocated resources.
 */
Hummer::~Hummer()
{
}

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
void Hummer::applyEffect(Player& player)
{
    player.addHummerEffect();
}

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
void Hummer::removeEffect(Player& player)
{
    player.removeHummerEffect();
}