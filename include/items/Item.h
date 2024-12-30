#ifndef ITEM_H
#define ITEM_H

#include "Cell.h"
#include "Player.h"
#include <iostream>
#include <string>

/**
 * @brief Abstract base class representing an item within the labyrinth.
 * 
 * @details 
 * The Item class serves as a base for various types of items that can be found
 * within the labyrinth. Each item has a position, effect duration, and state flags
 * indicating whether it is active or has been used. Derived classes must implement
 * the `applyEffect` and `removeEffect` methods to define specific behaviors.
 * 
 * Author: Roman Avanesov
 * Created: 25.12.2024
 * Last Modified: 30.12.2024
 */
class Item
{
    protected:

        Cell position;              ///< The position of the item within the labyrinth.
        int effectDuration;         ///< The duration for which the item's effect remains active.
        bool active;                ///< Flag indicating whether the item's effect is currently active.
        bool used;                  ///< Flag indicating whether the item has been used.
        std::string takeMessage;    ///< Message displayed when the player picks up the item.
        std::string removeMessage;  ///< Message displayed when the item's effect is removed.
        std::string infoMessage;    ///< Informational message about the item.

    public:

        /**
         * @brief Applies the item's effect to the player.
         * 
         * @param player Reference to the player object to which the effect is applied.
         * 
         * @details 
         * This pure virtual function must be overridden by derived classes to implement
         * specific behaviors when the player picks up the item.
         */
        virtual void applyEffect(Player& player) = 0;

        /**
         * @brief Removes the item's effect from the player.
         * 
         * @param player Reference to the player object from which the effect is removed.
         * 
         * @details 
         * This pure virtual function must be overridden by derived classes to implement
         * the removal of specific effects when the item's duration expires or it is deactivated.
         */
        virtual void removeEffect(Player& player) = 0;
        
        /**
         * @brief Activates the item's effect.
         * 
         * @details 
         * Sets the `active` flag to `true`, indicating that the item's effect is currently active.
         */
        void activate();

        /**
         * @brief Deactivates the item's effect.
         * 
         * @details 
         * Sets the `active` flag to `false`, indicating that the item's effect is no longer active.
         */
        void deactivate();
        
        /**
         * @brief Checks if the item has been used.
         * 
         * @return true If the item has been marked as used.
         * @return false Otherwise.
         * 
         * @details 
         * Allows other components to determine whether the item is still available for use
         * or has already been consumed.
         */
        bool isUsed();

        /**
         * @brief Marks the item as used.
         * 
         * @details 
         * Sets the `used` flag to `true`, indicating that the item has been utilized and should no longer be active.
         */
        void setUsed();

        /**
         * @brief Sets the duration for which the item's effect remains active.
         * 
         * @param effectDuration The number of turns or time units the effect should last.
         * 
         * @details 
         * Updates the `effectDuration` attribute to manage how long the item's effect will persist.
         */
        void setEffectDuration(int effectDuration);

        /**
         * @brief Sets the position of the item within the labyrinth.
         * 
         * @param position The `Cell` object representing the item's new position.
         * 
         * @details 
         * Updates the `position` attribute to reflect the item's location within the labyrinth grid.
         */
        void setPosition(Cell position);

        /**
         * @brief Retrieves the current position of the item.
         * 
         * @return Cell The `Cell` object representing the item's position.
         * 
         * @details 
         * Provides access to the item's `position` attribute, allowing other components to determine
         * where the item is located within the labyrinth.
         */
        Cell getPosition() const;

        /**
         * @brief Checks if the item's effect is currently active.
         * 
         * @return true If the item's effect is active.
         * @return false Otherwise.
         * 
         * @details 
         * Provides a way to verify whether the item's effect is influencing the game state at the moment.
         */
        bool isActive() const;

        /**
         * @brief Retrieves the remaining duration of the item's effect.
         * 
         * @return int The number of turns or time units left for the effect.
         * 
         * @details 
         * Allows the game to track and decrement the `effectDuration`, ensuring that effects expire appropriately.
         */
        int getEffectDuration() const;
    
        /**
         * @brief Displays the informational message associated with the item.
         * 
         * @details 
         * Outputs the `infoMessage` to the console with a yellow background for visibility.
         * This message typically describes the item's effect or usage instructions.
         */
        void printInfoMessage();

        /**
         * @brief Displays the message when the player picks up the item.
         * 
         * @details 
         * Outputs the `takeMessage` to the console with a yellow background, informing the player about the successful acquisition of the item.
         */
        void printTakeMessage();

        /**
         * @brief Displays the message when the item's effect is removed.
         * 
         * @details 
         * Outputs the `removeMessage` to the console with a yellow background, notifying the player that the item's effect has expired or been deactivated.
         */
        void printRemoveMessage();

        /**
         * @brief Constructs an Item object with a specified position and effect duration.
         * 
         * @param position The `Cell` object representing the item's position within the labyrinth.
         * @param effectDuration The duration for which the item's effect remains active. Defaults to 3.
         * 
         * @details 
         * Initializes the item with the given position and effect duration. Sets the `active` and `used` flags to `false`.
         */
        Item(Cell position, int effectDuration = 3) 
            : position(position), effectDuration(effectDuration), active(false), used(false) {};

        /**
         * @brief Constructs an Item object with specified row and column indices and effect duration.
         * 
         * @param row The row index of the item's position within the labyrinth.
         * @param col The column index of the item's position within the labyrinth.
         * @param effectDuration The duration for which the item's effect remains active. Defaults to 3.
         * 
         * @details 
         * Initializes the item with the given row and column indices, creating a `Cell` object for its position.
         * Sets the `active` and `used` flags to `false`.
         */
        Item(int row, int col, int effectDuration = 3) 
            : position(row, col, 'P'), effectDuration(effectDuration), active(false), used(false) {};
        
        /**
         * @brief Virtual destructor for the Item class.
         * 
         * @details 
         * Ensures that derived class destructors are called appropriately when deleting objects through base class pointers.
         */
        virtual ~Item();
    
};

#endif // ITEM_H