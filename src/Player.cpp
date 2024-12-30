#include "Player.h"

/**
 * @brief Default constructor for the Player class.
 * 
 * @details Initializes the player's position and sets all effect flags to false.
 */
Player::Player()
{
    // Initialize player position and effects if necessary
    // For example, setting the starting position can be done here
}

/**
 * @brief Destructor for the Player class.
 * 
 * @details Currently does not perform any specific actions.
 */
Player::~Player()
{
    // Cleanup resources if any (currently none)
}

/**
 * @brief Retrieves the current position of the player.
 * 
 * @return Cell The current position of the player.
 */
Cell Player::getPosition() const
{
    return this->position;
}

/**
 * @brief Sets the player's position in the labyrinth.
 * 
 * @param position The new position to set for the player.
 */
void Player::setPosition(const Cell& position)
{
    this->position = position;
}

/**
 * @brief Activates the sword effect for the player.
 * 
 * @details Grants the ability to destroy the Minotaur.
 */
void Player::addSwordEffect()
{
    this->swordEffect = true;
    // Additional logic can be added here if needed
}

/**
 * @brief Deactivates the sword effect for the player.
 * 
 * @details Removes the ability to destroy the Minotaur.
 */
void Player::removeSwordEffect()
{
    this->swordEffect = false;
    // Additional logic can be added here if needed
}

/**
 * @brief Activates the shield effect for the player.
 * 
 * @details Grants the ability to defend against the Minotaur.
 */
void Player::addShieldEffect()
{
    this->shieldEffect = true;
    // Additional logic can be added here if needed
}

/**
 * @brief Deactivates the shield effect for the player.
 * 
 * @details Removes the ability to defend against the Minotaur.
 */
void Player::removeShieldEffect()
{
    this->shieldEffect = false;
    // Additional logic can be added here if needed
}

/**
 * @brief Activates the hummer effect for the player.
 * 
 * @details Grants the ability to pass through walls.
 */
void Player::addHummerEffect()
{
    this->hummerEffect = true;
    // Additional logic can be added here if needed
}

/**
 * @brief Deactivates the hummer effect for the player.
 * 
 * @details Removes the ability to pass through walls.
 */
void Player::removeHummerEffect()
{
    this->hummerEffect = false;
    // Additional logic can be added here if needed
}

/**
 * @brief Activates the fog of war effect for the player.
 * 
 * @details Reduces the player's visibility to a 3x3 submatrix.
 */
void Player::addFogOfWarEffect()
{
    this->fogOfWarEffect = true;
    // Additional logic can be added here if needed
}

/**
 * @brief Deactivates the fog of war effect for the player.
 * 
 * @details Restores the player's full visibility in the labyrinth.
 */
void Player::removeFogOfWarEffect()
{
    this->fogOfWarEffect = false;
    // Additional logic can be added here if needed
}