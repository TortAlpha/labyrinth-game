#include "items/FogOfWar.h"

/**
 * @brief Destructor for the FogOfWar class.
 * 
 * @details 
 * Currently does not perform any specific actions as there are no dynamically allocated resources.
 */
FogOfWar::~FogOfWar()
{
}

/**
 * @brief Applies the Fog of War effect to the player.
 * 
 * @param player Reference to the Player object to which the effect is applied.
 * 
 * @details 
 * Activates the Fog of War effect for the player by calling the player's `addFogOfWarEffect` method.
 * This effect typically limits the player's visibility within the labyrinth.
 */
void FogOfWar::applyEffect(Player& player)
{
    player.addFogOfWarEffect();
}

/**
 * @brief Removes the Fog of War effect from the player.
 * 
 * @param player Reference to the Player object from which the effect is removed.
 * 
 * @details 
 * Deactivates the Fog of War effect for the player by calling the player's `removeFogOfWarEffect` method.
 * This restores the player's full visibility within the labyrinth.
 */
void FogOfWar::removeEffect(Player& player)
{
    player.removeFogOfWarEffect();
}