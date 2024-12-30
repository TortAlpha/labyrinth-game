#include "items/Sword.h"

/**
 * @brief Destructor for the Sword class.
 * 
 * @details 
 * Currently does not perform any specific actions as there are no dynamically allocated resources.
 */
Sword::~Sword()
{
}

/**
 * @brief Applies the Sword effect to the player.
 * 
 * @param player Reference to the Player object to which the effect is applied.
 * 
 * @details 
 * Activates the Sword effect by invoking the player's `addSwordEffect` method.
 * This effect typically enhances the player's ability to attack enemies within a certain range,
 * allowing for more effective combat against the minotaur.
 */
void Sword::applyEffect(Player& player)
{
    player.addSwordEffect();
}

/**
 * @brief Removes the Sword effect from the player.
 * 
 * @param player Reference to the Player object from which the effect is removed.
 * 
 * @details 
 * Deactivates the Sword effect by invoking the player's `removeSwordEffect` method.
 * This removes the enhanced attack capabilities from the player, reverting them to their normal state.
 */
void Sword::removeEffect(Player& player)
{
    player.removeSwordEffect();
}