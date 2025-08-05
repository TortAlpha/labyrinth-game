#ifndef GAME_H
#define GAME_H

#include "Labyrinth.h"
#include "Player.h"
#include "Minotaur.h"
#include "Logger.h"
#include "items/Item.h"
#include <list>

/**
 * @brief The Game class manages the overall game state, including the labyrinth, player, minotaur, and items.
 * 
 * @details 
 * Handles the initialization of the game components, spawning of entities, game loop management,
 * player and minotaur movements, collision detection, and rendering of the game map. Utilizes a Logger
 * to record significant game events and state changes.
 * 
 * Author: Roman Avanesov
 * Created: 25.12.2024
 * Last Modified: 30.12.2024
 */
class Game
{
private:
    
    Labyrinth* labyrinth;           ///< Pointer to the labyrinth representing the game map.
    Player* player;                 ///< Pointer to the player entity.
    Minotaur* minotaur;             ///< Pointer to the minotaur entity.
    std::list<Item*> items;         ///< List of pointers to items present in the labyrinth.
    int numItems;                   ///< Number of items to spawn in the labyrinth.
    uint64_t game_init_time = 0;  ///< Time taken to initialize the game in milliseconds.

    // Logger object to log game events
    Logger logger;

    // Enumeration to represent the game state
    enum GAME_STATE {
        PLAYING,     ///< The game is currently in progress.
        PLAYER_WON,  ///< The player has successfully completed the game.
        PLAYER_LOST, ///< The player has been defeated by the minotaur.
        QUIT         ///< The player has chosen to quit the game.
    };

    GAME_STATE state;               ///< Current state of the game.

    // Game initialization methods

    /**
     * @brief Initializes the game components with quiet mode option.
     * 
     * @param width The width of the labyrinth.
     * @param height The height of the labyrinth.
     * @param quiet Whether to enable quiet mode for the labyrinth.
     * @param exitOnFailure Whether to exit the program on map generation failure (default: true).
     * 
     * @details 
     * Sets up the labyrinth grid with quiet mode, checks for successful generation, and initializes the player and minotaur entities.
     */
    void init(unsigned int width, unsigned int height, bool quiet, bool exitOnFailure = true);

    /**
     * @brief Spawns the player, minotaur, and randomly places items in the labyrinth.
     * 
     * @details 
     * Positions the player at the start point, places the minotaur along the generated path, and randomly distributes items ensuring they are placed on empty cells.
     */
    void spawn();

    // Helper methods

    /**
     * @brief Determines if a specific cell is a wall or the entrance.
     * 
     * @param position The cell position to check.
     * @return true If the cell is a wall ('#') or the entrance ('U').
     * @return false Otherwise.
     */
    bool isWall(const Cell& position) const;

    /**
     * @brief Determines if a specific cell is on the border of the labyrinth.
     * 
     * @param position The cell position to check.
     * @return true If the cell is on the border.
     * @return false Otherwise.
     */
    bool isMapBorder(const Cell& position) const;

    // Game logic methods

    /**
     * @brief Checks and handles collisions between the player, minotaur, and items.
     * 
     * @details 
     * - If the player collides with the minotaur and is not immune, the game state is updated to PLAYER_LOST.
     * - If the player reaches the exit, the game state is updated to PLAYER_WON.
     * - Handles interactions with items, activating or deactivating them based on collisions.
     */
    void checkGameObjectCollision();

    /**
     * @brief Updates the player's position based on the input command.
     * 
     * @param command The input command character ('w', 'a', 's', 'd', etc.).
     * 
     * @details 
     * Moves the player in the specified direction if the target cell is not a wall.
     * Handles interactions with walls if the player has the Hummer effect.
     * Updates active item effects and logs the player's actions.
     */
    void playerMovementUpdate(char command);

    /**
     * @brief Moves the minotaur randomly within the labyrinth, avoiding walls and the exit.
     * 
     * @details 
     * Attempts to move the minotaur in a random direction up to a maximum number of attempts.
     * Ensures the minotaur does not move into walls or the exit point.
     * Logs the minotaur's new position after a successful move.
     */
    void minotaurMovementUpdate();

    /**
     * @brief Updates the duration of active item effects and removes them if expired.
     * 
     * @details 
     * Iterates through all items, decrementing their effect durations. If an item's effect duration reaches zero,
     * the effect is removed from the player, and the item is deactivated and marked as used.
     */
    void itemsEffectUpdate();

    /**
     * @brief Allows the player to attack and kill the minotaur if it is within attack range.
     * 
     * @details 
     * If the player has the Sword effect, this method checks all cells within a 1-cell radius around the player.
     * If the minotaur is found within this range, it is killed, the Sword effect is removed, and the action is logged.
     * If no minotaur is within range, an appropriate message is logged.
     */
    void attackMinotaur();

    // Print methods

    /**
     * @brief Renders the current state of the labyrinth to the console.
     * 
     * @details 
     * Clears the console and prints the labyrinth. If the player has the Fog of War effect active,
     * it limits the visibility based on the player's position.
     */
    void printMap();

    /**
     * @brief Displays the "Game Over" ASCII art message.
     * 
     * @details 
     * Outputs a stylized "Game Over" message in red color to the console.
     */
    void printGameOver();

    /**
     * @brief Displays the "You Won" ASCII art message.
     * 
     * @details 
     * Outputs a stylized "You Won" message in green color to the console.
     */
    void printGameWon();

public:
    /**
     * @brief Constructs a Game object with specified dimensions and number of items.
     * 
     * @param width The width of the labyrinth.
     * @param height The height of the labyrinth.
     * @param numItems The number of items to spawn in the labyrinth.
     * @param startGame Whether to automatically start the game loop (default: true for backward compatibility).
     * 
     * @details 
     * Initializes the game by setting up the labyrinth, spawning entities. If startGame is true, starts the game loop.
     */
    Game(unsigned int width, unsigned int height, unsigned int numItems, bool startGame = true);

    /**
     * @brief Constructs a Game object with specified dimensions, items count, game start flag, and quiet mode.
     * 
     * @param width The width of the labyrinth.
     * @param height The height of the labyrinth.
     * @param numItems The number of items to spawn in the labyrinth.
     * @param startGame Whether to automatically start the game loop.
     * @param quiet Whether to enable quiet mode for the labyrinth.
     * 
     * @details 
     * Initializes the game by setting up the labyrinth with quiet mode, spawning entities. If startGame is true, starts the game loop.
     */
    Game(unsigned int width, unsigned int height, unsigned int numItems, bool startGame, bool quiet);

    /**
     * @brief Constructs a Game object for testing with non-exit behavior on map generation failure.
     * 
     * @param width The width of the labyrinth.
     * @param height The height of the labyrinth.
     * @param numItems The number of items to spawn in the labyrinth.
     * @param startGame Whether to automatically start the game loop.
     * @param quiet Whether to enable quiet mode for the labyrinth.
     * @param exitOnFailure Whether to exit on map generation failure.
     * 
     * @details 
     * Initializes the game by setting up the labyrinth with quiet mode and exit behavior control, spawning entities. If startGame is true, starts the game loop.
     */
    Game(unsigned int width, unsigned int height, unsigned int numItems, bool startGame, bool quiet, bool exitOnFailure);

    /**
     * @brief Starts the game loop if not already started.
     * 
     * @details 
     * This method can be called to explicitly start the game loop after construction.
     * Useful for testing scenarios where you want to set up the game without immediately starting.
     */
    void start();

    /**
     * @brief Gets the current labyrinth instance.
     * 
     * @return Pointer to the labyrinth object.
     * 
     * @details 
     * Provides access to the labyrinth for testing purposes.
     */
    Labyrinth* getLabyrinth() const;

    /**
     * @brief Gets the current player instance.
     * 
     * @return Pointer to the player object.
     * 
     * @details 
     * Provides access to the player for testing purposes.
     */
    Player* getPlayer() const;

    /**
     * @brief Gets the current minotaur instance.
     * 
     * @return Pointer to the minotaur object.
     * 
     * @details 
     * Provides access to the minotaur for testing purposes.
     */
    Minotaur* getMinotaur() const;

    /**
     * @brief Checks if the labyrinth was successfully generated.
     * 
     * @return true if labyrinth generation was successful, false otherwise.
     * 
     * @details 
     * Useful for testing to verify that the game initialization was successful.
     */
    bool isLabyrinthGenerated() const;

    /**
     * @brief Destructor for the Game class.
     * 
     * @details 
     * Deallocates all dynamically allocated memory, including the labyrinth, player, minotaur, and items,
     * to prevent memory leaks.
     */
    ~Game();

    /**
     * @brief Starts and manages the main game loop, handling player input, minotaur movement, collisions, and rendering.
     * 
     * @details 
     * Continuously updates the game state by processing player commands, moving the minotaur at regular intervals,
     * checking for collisions, and rendering the labyrinth. Displays active effects on the player and handles game termination.
     */
    void updateGameState();
};

#endif // GAME_H