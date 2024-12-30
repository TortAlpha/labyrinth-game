#include "items/Shield.h"

/**
 * @brief Destructor for the Shield class.
 * 
 * @details 
 * Currently does not perform any specific actions as there are no dynamically allocated resources.
 */
Shield::~Shield()
{
}

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
void Shield::applyEffect(Player& player)
{
    player.addShieldEffect();
}

/**
 * @brief Removes the Shield effect from the player.
 * 
 * @param player Reference to the Player object from which the effect is removed.
 * 
 * @details 
 * Deactivates the Shield effect by invoking the player's `removeShieldEffect` method.
 * This removes the temporary protection, returning the player to their normal state of vulnerability.
 */
void Shield::removeEffect(Player& player)
{
    player.removeShieldEffect();
}