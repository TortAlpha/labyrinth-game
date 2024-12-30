#include "items/Item.h"
#include "termcolor.hpp"

/**
 * @brief Destructor for the Item class.
 * 
 * @details 
 * Currently does not perform any specific actions as there are no dynamically allocated resources.
 */
Item::~Item()
{
}

/**
 * @brief Activates the item's effect.
 * 
 * @details 
 * Sets the `active` flag to `true`, indicating that the item's effect is currently active.
 */
void Item::activate()
{
    active = true;
}

/**
 * @brief Deactivates the item's effect.
 * 
 * @details 
 * Sets the `active` flag to `false`, indicating that the item's effect is no longer active.
 */
void Item::deactivate()
{
    active = false;
}

/**
 * @brief Sets the duration for which the item's effect remains active.
 * 
 * @param effectDuration The number of turns or time units the effect should last.
 * 
 * @details 
 * Updates the `effectDuration` attribute to manage how long the item's effect will persist.
 */
void Item::setEffectDuration(int effectDuration)
{
    this->effectDuration = effectDuration;
}

/**
 * @brief Sets the position of the item within the labyrinth.
 * 
 * @param position The `Cell` object representing the item's new position.
 * 
 * @details 
 * Updates the `position` attribute to reflect the item's location within the labyrinth grid.
 */
void Item::setPosition(Cell position)
{
    this->position = position;
}

/**
 * @brief Retrieves the current position of the item.
 * 
 * @return Cell The `Cell` object representing the item's position.
 * 
 * @details 
 * Provides access to the item's `position` attribute, allowing other components to determine
 * where the item is located within the labyrinth.
 */
Cell Item::getPosition() const
{
    return position;
}

/**
 * @brief Marks the item as used.
 * 
 * @details 
 * Sets the `used` flag to `true`, indicating that the item has been utilized and should no longer be active.
 */
void Item::setUsed()
{
    used = true;
}

/**
 * @brief Checks if the item has been used.
 * 
 * @return true If the item has been marked as used.
 * @return false Otherwise.
 * 
 * @details 
 * Allows other components to determine whether the item is still available for use or has already been consumed.
 */
bool Item::isUsed()
{
    return used;
}

/**
 * @brief Checks if the item's effect is currently active.
 * 
 * @return true If the item's effect is active.
 * @return false Otherwise.
 * 
 * @details 
 * Provides a way to verify whether the item's effect is influencing the game state at the moment.
 */
bool Item::isActive() const
{
    return active;
}

/**
 * @brief Retrieves the remaining duration of the item's effect.
 * 
 * @return int The number of turns or time units left for the effect.
 * 
 * @details 
 * Allows the game to track and decrement the `effectDuration`, ensuring that effects expire appropriately.
 */
int Item::getEffectDuration() const
{
    return effectDuration;
}

/**
 * @brief Displays the informational message associated with the item.
 * 
 * @details 
 * Outputs the `infoMessage` to the console with a yellow background for visibility.
 * This message typically describes the item's effect or usage instructions.
 */
void Item::printInfoMessage()
{
    std::cout << termcolor::on_yellow << infoMessage << termcolor::reset << std::endl;
}

/**
 * @brief Displays the message when the player picks up the item.
 * 
 * @details 
 * Outputs the `takeMessage` to the console with a yellow background, informing the player about the successful acquisition of the item.
 */
void Item::printTakeMessage()
{
    std::cout << termcolor::on_yellow << takeMessage << termcolor::reset << std::endl;
}

/**
 * @brief Displays the message when the item's effect is removed.
 * 
 * @details 
 * Outputs the `removeMessage` to the console with a yellow background, notifying the player that the item's effect has expired or been deactivated.
 */
void Item::printRemoveMessage()
{
    std::cout << termcolor::on_yellow << removeMessage << termcolor::reset << std::endl;
}