// Game.cpp

#include "Game.h"
#include "Labyrinth.h"
#include "Player.h"
#include "Cell.h"
#include "Input.h"
#include "termcolor.hpp"
#include "items/Item.h"
#include "items/FogOfWar.h"
#include "items/Hummer.h"
#include "items/Shield.h"
#include "items/Sword.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>

/**
 * @brief Constructs a Game object with specified dimensions and number of items.
 * 
 * @param width The width of the labyrinth.
 * @param height The height of the labyrinth.
 * @param numItems The number of items to spawn in the labyrinth.
 * 
 * @details 
 * Initializes the game by setting up the labyrinth, spawning entities, and starting the game loop.
 */
Game::Game(unsigned int width, unsigned int height, unsigned int numItems)
    : logger("game.log"), state(GAME_STATE::PLAYING), numItems(numItems)
{
    init(width, height);      // Initialize the labyrinth and game entities
    spawn();                   // Spawn player, minotaur, and items
    labyrinth->print();        // Display the initial state of the labyrinth
    updateGameState();         // Start the game loop
}

// Initializes the labyrinth, player, minotaur, and item list
/**
 * @brief Initializes the game components including the labyrinth, player, minotaur, and items.
 * 
 * @param width The width of the labyrinth.
 * @param height The height of the labyrinth.
 * 
 * @details 
 * Sets up the labyrinth grid, checks for successful generation, and initializes the player and minotaur entities.
 */
void Game::init(unsigned int width, unsigned int height)
{
    logger.log("Game init with width: " + std::to_string(width) + " and height: " + std::to_string(height));

    // Dynamically allocate the labyrinth
    labyrinth = new Labyrinth(width, height);

    // Check if labyrinth generation was successful
    if (!labyrinth->getMapGenerationSuccess()) {
        std::cout << "Try again.\n";
        logger.log("Map generation failed. Exiting...");
        exit(1);
    }
    logger.log("Map generated successfully.");

    // Log start and end points of the labyrinth
    logger.log("Start point: " + std::to_string(labyrinth->getStartPoint().getRow()) + " " + std::to_string(labyrinth->getStartPoint().getCol()));
    logger.log("End point: " + std::to_string(labyrinth->getEndPoint().getRow()) + " " + std::to_string(labyrinth->getEndPoint().getCol()));

    // Initialize game entities
    items = std::list<Item*>();      // Initialize the items list
    player = new Player();           // Dynamically allocate the player
    minotaur = new Minotaur();       // Dynamically allocate the minotaur
}

// Spawns the player, minotaur, and randomly places items in the labyrinth
/**
 * @brief Spawns the player, minotaur, and items within the labyrinth.
 * 
 * @details 
 * Positions the player at the start point, places the minotaur along the generated path, and randomly distributes items ensuring they are placed on empty cells.
 */
void Game::spawn()
{
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator

    // Lambda function to generate a random number between min and max (inclusive)
    auto randomNumBetween = [](int min, int max) -> int {
        return min + (rand() % (max - min + 1));
    };

    // Spawn the Player
    Cell startPoint = labyrinth->getStartPoint();
    startPoint.setRow(startPoint.getRow() + 1); // Adjust player starting position
    player->setPosition(startPoint);
    labyrinth->getCell(startPoint.getRow(), startPoint.getCol()).setVal('R'); // 'R' represents the player

    logger.log("Player spawned at: " + std::to_string(startPoint.getRow()) + " " + std::to_string(startPoint.getCol()));

    // Spawn the Minotaur at a random position along the path
    std::list<Cell*> path = labyrinth->getPathFromEntranceToExit();
    if (path.size() < 14) { // Ensure there's enough space to avoid out-of-range
        logger.log("Path too short to spawn minotaur. Exiting...");
        exit(1);
    }
    int rndPos = randomNumBetween(7, static_cast<int>(path.size()) - 7); // Avoid spawning too close to start/end
    auto it = path.begin();
    std::advance(it, rndPos);
    Cell* minotaurPos = *it;
    minotaur->setPosition(*minotaurPos);
    labyrinth->getCell(minotaurPos->getRow(), minotaurPos->getCol()).setVal('M'); // 'M' represents the minotaur

    logger.log("Minotaur spawned at: " + std::to_string(minotaurPos->getRow()) + " " + std::to_string(minotaurPos->getCol()));

    // Lambda function to check if a position is suitable for placing an item
    auto checkPosForItem = [&](const Cell& pos) -> bool {
        return labyrinth->getCell(pos.getRow(), pos.getCol()).getVal() == ' ';
    };

    // Spawn Items
    for (unsigned int i = 0; i < numItems; ++i)
    {
        int rndNum = rand() % 4; // Randomly choose item type (0-3)

        // Generate a random position within the labyrinth boundaries (excluding borders)
        Cell item_pos(
            randomNumBetween(1, labyrinth->getHeight() - 2),
            randomNumBetween(1, labyrinth->getWidth() - 2),
            'P' // 'P' represents a generic item
        );

        // Ensure the item is placed on an empty cell
        while (!checkPosForItem(item_pos)) {
            item_pos.setRow(randomNumBetween(1, labyrinth->getHeight() - 2));
            item_pos.setCol(randomNumBetween(1, labyrinth->getWidth() - 2));
        }

        logger.log("Generated position for item: " + std::to_string(item_pos.getRow()) + " " + std::to_string(item_pos.getCol()));

        // Instantiate the appropriate item based on rndNum
        Item* newItem = nullptr;

        switch (rndNum)
        {
            case 0:
                newItem = new FogOfWar(item_pos);
                break;
            case 1:
                newItem = new Hummer(item_pos);
                break;
            case 2:
                newItem = new Shield(item_pos);
                break;
            case 3:
                newItem = new Sword(item_pos);
                break;
            default:
                logger.log("Problem with item spawn.");
                break;
        }

        // Add the new item to the items list and update the labyrinth cell
        if (newItem) {
            logger.log("Item spawned at: " 
                + std::to_string(newItem->getPosition().getRow()) + " " 
                + std::to_string(newItem->getPosition().getCol()));
            labyrinth->setCell(item_pos.getRow(), item_pos.getCol(), Cell(item_pos.getRow(), item_pos.getCol(), 'P'));
            items.push_back(newItem); // Store the raw pointer
        }
    }
}

// Checks if a given position is a wall or entrance
/**
 * @brief Determines if a specific cell is a wall or the entrance.
 * 
 * @param position The cell position to check.
 * @return true If the cell is a wall ('#') or the entrance ('U').
 * @return false Otherwise.
 */
bool Game::isWall(const Cell& position) const {
    char cellVal = labyrinth->getCell(position.getRow(), position.getCol()).getVal();
    return cellVal == '#' || cellVal == 'U';
}

// Checks if a given position is on the border of the map
/**
 * @brief Determines if a specific cell is on the border of the labyrinth.
 * 
 * @param position The cell position to check.
 * @return true If the cell is on the border.
 * @return false Otherwise.
 */
bool Game::isMapBorder(const Cell& position) const {
    return position.getRow() == 0 || position.getRow() == labyrinth->getHeight() - 1 ||
           position.getCol() == 0 || position.getCol() == labyrinth->getWidth() - 1;
}

// Updates the player's movement based on input command
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
void Game::playerMovementUpdate(char command) {
    Cell potential_pos;

    // Determine the potential new position based on the command
    switch (command)
    {
        case 'w': // Move Up
            potential_pos = Cell(player->getPosition().getRow() - 1, player->getPosition().getCol(), 'R');
            break;

        case 's': // Move Down
            potential_pos = Cell(player->getPosition().getRow() + 1, player->getPosition().getCol(), 'R');
            break;

        case 'a': // Move Left
            potential_pos = Cell(player->getPosition().getRow(), player->getPosition().getCol() - 1, 'R');
            break;

        case 'd': // Move Right
            potential_pos = Cell(player->getPosition().getRow(), player->getPosition().getCol() + 1, 'R');
            break;

        default:
            return; // Ignore invalid commands
    }

    // Check if the potential position is not a wall
    if (!isWall(potential_pos)) {

        // Clear the player's current position in the labyrinth
        labyrinth->getCell(player->getPosition().getRow(), player->getPosition().getCol()).setVal(' ');

        // Update the player's position
        player->setPosition(potential_pos);

        // Set the new position in the labyrinth to 'R' (player)
        labyrinth->getCell(potential_pos.getRow(), potential_pos.getCol()).setVal('R');

        // If the player is immune to the minotaur, decrease the immunity duration
        if (player->isImmuneToMinotaur()) {
            player->decreaseImmuneDuration();
        }

        // Update active item effects
        itemsEffectUpdate();

        // Log the player's action and new position
        logger.log("Action: " + std::string(1, command));
        logger.log("Player moved to: " + std::to_string(player->getPosition().getRow()) + " " + std::to_string(player->getPosition().getCol()));

        return;
    }

    // If the potential position is a wall and the player has the Hummer effect
    if (player->hasHummerEffect()) {

        // Prevent the player from moving to the map border
        if (isMapBorder(potential_pos)) return;

        // Remove the Hummer effect after using it to destroy a wall
        player->removeHummerEffect();

        // Clear the player's current position in the labyrinth
        labyrinth->getCell(player->getPosition().getRow(), player->getPosition().getCol()).setVal(' ');

        // Update the player's position to the wall's position
        player->setPosition(potential_pos);

        // Set the new position in the labyrinth to 'R' (player)
        labyrinth->getCell(potential_pos.getRow(), potential_pos.getCol()).setVal('R');

        // If the player is immune to the minotaur, decrease the immunity duration
        if (player->isImmuneToMinotaur()) {
            player->decreaseImmuneDuration();
        }

        // Update active item effects
        itemsEffectUpdate();

        // Log the player's action and new position
        logger.log("Action: " + std::string(1, command));
        logger.log("Player moved to: " + std::to_string(player->getPosition().getRow()) + " " + std::to_string(player->getPosition().getCol()));
    }
}

// Updates the minotaur's position randomly, avoiding walls and the end point
/**
 * @brief Moves the minotaur randomly within the labyrinth, avoiding walls and the exit.
 * 
 * @details 
 * Attempts to move the minotaur in a random direction up to a maximum number of attempts.
 * Ensures the minotaur does not move into walls or the exit point.
 * Logs the minotaur's new position after a successful move.
 */
void Game::minotaurMovementUpdate()
{
    Cell minotaur_pos = minotaur->getPosition();

    const int MAX_ATTEMPTS = 4; // Maximum attempts to move
    bool moved = false;

    // Attempt to move the minotaur up to MAX_ATTEMPTS times
    for (int attempt = 0; attempt < MAX_ATTEMPTS && !moved; ++attempt)
    {
        int randomDirection = rand() % 4; // Randomly choose a direction
        Cell potential_pos;

        // Determine the potential new position based on the random direction
        switch (randomDirection) {
            case 0: // Move Up
                potential_pos = Cell(minotaur_pos.getRow() - 1, minotaur_pos.getCol(), 'M');
                break;
            case 1: // Move Down
                potential_pos = Cell(minotaur_pos.getRow() + 1, minotaur_pos.getCol(), 'M');
                break;
            case 2: // Move Left
                potential_pos = Cell(minotaur_pos.getRow(), minotaur_pos.getCol() - 1, 'M');
                break;
            case 3: // Move Right
                potential_pos = Cell(minotaur_pos.getRow(), minotaur_pos.getCol() + 1, 'M');
                break;
            default:
                break;
        }

        // Check if the potential position is not a wall
        if (!isWall(potential_pos)) {

            // Ensure the minotaur does not move to the end point
            if (potential_pos == labyrinth->getEndPoint()) continue;

            // Clear the minotaur's current position in the labyrinth
            labyrinth->getCell(minotaur_pos.getRow(), minotaur_pos.getCol()).setVal(' ');

            // Update the minotaur's position
            minotaur->setPosition(potential_pos);

            // Set the new position in the labyrinth to 'M' (minotaur)
            labyrinth->getCell(potential_pos.getRow(), potential_pos.getCol()).setVal('M');

            moved = true; // Mark as moved to exit the loop
        }
    }

    // Log the minotaur's new position
    logger.log("Minotaur moved to: " + std::to_string(minotaur->getPosition().getRow()) + " " + std::to_string(minotaur->getPosition().getCol()));
}

// Handles collisions between the player, minotaur, and items
/**
 * @brief Checks and handles collisions between the player, minotaur, and items.
 * 
 * @details 
 * - If the player collides with the minotaur and is not immune, the game state is updated to PLAYER_LOST.
 * - If the player reaches the exit, the game state is updated to PLAYER_WON.
 * - Handles interactions with items, activating or deactivating them based on collisions.
 */
void Game::checkGameObjectCollision()
{
    // Check if the player and minotaur occupy the same position and the player is not immune
    if (player->getPosition() == minotaur->getPosition() && minotaur->isAlive() && !player->isImmuneToMinotaur()) 
    {
        if (player->hasShieldEffect()) {
            player->removeShieldEffect(); // Absorb the attack with the shield
            player->setImmuneToMinotaur(true, 2); // Grant temporary immunity
        }
        else {
            state = GAME_STATE::PLAYER_LOST; // Player is defeated by the minotaur
            labyrinth->getCell(player->getPosition().getRow(), player->getPosition().getCol()).setVal('M');
            logger.log("Game state updated: " + std::to_string(state));
            return;
        }
    }

    // Check if the player has reached the end point
    if (player->getPosition() == labyrinth->getEndPoint())
    {
        state = GAME_STATE::PLAYER_WON; // Player wins the game
        logger.log("Game state updated: " + std::to_string(state));
        return;
    }

    // Iterate through all items to check for collisions
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        Item* currentItem = *it;

        // Player picks up an item
        if (currentItem->getPosition() == player->getPosition() && !currentItem->isUsed())
        {
            currentItem->activate();                 // Activate the item
            currentItem->applyEffect(*player);       // Apply the item's effect to the player
            currentItem->setUsed();                  // Mark the item as used to prevent reactivation
            labyrinth->getCell(player->getPosition().getRow(), player->getPosition().getCol()).setVal('R'); // Update cell symbol
            logger.log("Item activated at: " + std::to_string(currentItem->getPosition().getRow()) + " " + std::to_string(currentItem->getPosition().getCol()));
        }

        // Minotaur destroys an item
        if (currentItem->getPosition() == minotaur->getPosition() && !currentItem->isUsed())
        {
            currentItem->deactivate();                // Deactivate the item's effect
            currentItem->setUsed();                    // Mark the item as used
            logger.log("Item deactivated at: " + std::to_string(currentItem->getPosition().getRow()) + " " + std::to_string(currentItem->getPosition().getCol()));
        }
    }
}

// Updates the duration of active item effects and removes them if expired
/**
 * @brief Updates the duration of active item effects and removes them if their duration has expired.
 * 
 * @details 
 * Iterates through all items, decrementing their effect durations. If an item's effect duration reaches zero,
 * the effect is removed from the player, and the item is deactivated and marked as used.
 */
void Game::itemsEffectUpdate()
{
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        Item* currentItem = *it;
        if (currentItem->isActive())
        {
            currentItem->setEffectDuration(currentItem->getEffectDuration() - 1); // Decrease effect duration
            if (currentItem->getEffectDuration() == 0)
            {
                currentItem->removeEffect(*player); // Remove the effect from the player
                currentItem->deactivate();          // Deactivate the item
                currentItem->setUsed();             // Mark the item as used
                logger.log("Item deactivated at: " + std::to_string(currentItem->getPosition().getRow()) + " " + std::to_string(currentItem->getPosition().getCol()));
            }
        }
    }
}

// Allows the player to attack the minotaur within a radius of 1 cell around them
/**
 * @brief Allows the player to attack and kill the minotaur if it is within attack range.
 * 
 * @details 
 * If the player has the Sword effect, this method checks all cells within a 1-cell radius around the player.
 * If the minotaur is found within this range, it is killed, the Sword effect is removed, and the action is logged.
 * If no minotaur is within range, an appropriate message is logged.
 */
void Game::attackMinotaur() 
{
    if (player->hasSwordEffect()) 
    {
        int playerRow = player->getPosition().getRow();
        int playerCol = player->getPosition().getCol();

        int attackRadius = 1; // Define the attack radius (1 cell in each direction)

        // Iterate through all cells within the attack radius
        for (int dr = -attackRadius; dr <= attackRadius; ++dr) 
        {
            for (int dc = -attackRadius; dc <= attackRadius; ++dc) 
            {
                int targetRow = playerRow + dr;
                int targetCol = playerCol + dc;

                // Ensure the target cell is within the labyrinth boundaries
                if (targetRow >= 0 && targetRow < static_cast<int>(labyrinth->getHeight()) &&
                    targetCol >= 0 && targetCol < static_cast<int>(labyrinth->getWidth())) 
                {
                    char cellVal = labyrinth->getCell(targetRow, targetCol).getVal();

                    // Check if the minotaur is in the target cell
                    if (cellVal == 'M') 
                    {
                        labyrinth->getCell(targetRow, targetCol).setVal(' '); // Remove the minotaur from the cell
                        minotaur->kill();                                      // Kill the minotaur
                        player->removeSwordEffect();                           // Remove the sword effect from the player

                        logger.log("Minotaur attacked and killed at position: (" + 
                                   std::to_string(targetRow) + ", " + std::to_string(targetCol) + ")");

                        return; // Exit after killing the minotaur
                    }
                }
            }
        }

        // Log if no minotaur was found within the attack range
        logger.log("Attack attempted, but no minotaur found within attack range.");
    }
}

// Main game loop that updates the game state continuously until the game ends
/**
 * @brief Starts and manages the main game loop, handling player input, minotaur movement, collisions, and rendering.
 * 
 * @details 
 * Continuously updates the game state by processing player commands, moving the minotaur at regular intervals,
 * checking for collisions, and rendering the labyrinth. Displays active effects on the player and handles game termination.
 */
void Game::updateGameState()
{
    logger.log("Game state updated: " + std::to_string(state));
    srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator
    input::enableRawMode(); // Enable raw mode for capturing input without waiting for Enter

    auto lastMinotaurUpdate = std::chrono::steady_clock::now(); // Timestamp for minotaur's last move

    // Main game loop
    while (state == GAME_STATE::PLAYING)
    {	
        // Handle player input
        if (input::kbhit()) {
            char command = input::getch(); // Get the pressed key

            // Handle different commands
            switch (command) {
                case 'q': // Quit the game
                    state = GAME_STATE::QUIT;
                    logger.log("Game state updated: " + std::to_string(state));
                    break;
                case ' ': // Player attacks minotaur
                    attackMinotaur();
                    break;
                default: // Handle movement commands
                    playerMovementUpdate(command);
                    break;
            }
        }

        // Handle minotaur movement at fixed intervals (every 1 second)
        auto now = std::chrono::steady_clock::now();
        auto diffSec = std::chrono::duration<double>(now - lastMinotaurUpdate).count();

        if (diffSec >= 1.0 && minotaur->isAlive()) {
            minotaurMovementUpdate();            
            lastMinotaurUpdate = std::chrono::steady_clock::now();
        }

        // Check for collisions between game objects
        checkGameObjectCollision();

        // Render the current state of the map
        printMap();

        // Display active effects on the player with colored messages
        if (player->isImmuneToMinotaur()) {
            std::cout << termcolor::on_yellow << termcolor::bold 
                      << "Immune to Minotaur for " << player->getImmuneDuration() << " moves." 
                      << termcolor::reset << std::endl;
        }
        if (player->hasSwordEffect()) {
            std::cout << termcolor::on_bright_red << termcolor::bold 
                      << "Sword effect active." 
                      << termcolor::reset << std::endl;
        }
        if (player->hasShieldEffect()) {
            std::cout << termcolor::on_bright_green << termcolor::bold 
                      << "Shield effect active." 
                      << termcolor::reset << std::endl;
        }
        if (player->hasHummerEffect()) {
            std::cout << termcolor::bright_yellow << termcolor::bold 
                      << "Hummer effect active." 
                      << termcolor::reset << std::endl;
        }
        if (player->hasFogOfWarEffect()) {
            std::cout << termcolor::on_bright_grey << termcolor::bold 
                      << "Fog of War effect active." 
                      << termcolor::reset << std::endl;
        }

        // Small delay to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    // Final rendering after the game loop ends
    system("clear"); // Clear the console
    labyrinth->print(); // Print the final state of the labyrinth

    // Display the end game message based on the game state
    switch (state) {
        case GAME_STATE::PLAYER_WON:
            printGameWon();
            break;

        case GAME_STATE::PLAYER_LOST:
            printGameOver();
            break;
        default:
            break;
    }

    this->labyrinth->saveToFile("labyrinth.txt"); // Save the labyrinth to a file

    input::disableRawMode(); // Disable raw mode before exiting
}

// Renders the current state of the map, considering active effects like Fog of War
/**
 * @brief Renders the current state of the labyrinth to the console.
 * 
 * @details 
 * Clears the console and prints the labyrinth. If the player has the Fog of War effect active,
 * it limits the visibility based on the player's position.
 */
void Game::printMap() 
{
    // Clear the console screen
    std::cout << "\x1B[2J\x1B[H";

    // Use the appropriate print method based on whether Fog of War is active
    if (player->hasFogOfWarEffect()) {
        labyrinth->printWithFogOfWar(player->getPosition());
    } else {
        labyrinth->print();
    }
}

// Displays a "Game Over" ASCII art message
/**
 * @brief Displays the "Game Over" ASCII art message.
 * 
 * @details 
 * Outputs a stylized "Game Over" message in red color to the console.
 */
void Game::printGameOver() 
{
    std::cout << termcolor::red << termcolor::bold;
    std::cout << R"( ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ 
██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗
██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝
██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗
╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║
 ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝)" 
              << termcolor::reset << std::endl;
}

// Displays a "You Won" ASCII art message
/**
 * @brief Displays the "You Won" ASCII art message.
 * 
 * @details 
 * Outputs a stylized "You Won" message in green color to the console.
 */
void Game::printGameWon() 
{
    std::cout << termcolor::green << termcolor::bold;
    std::cout << R"(██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗ ██████╗ ███╗   ██╗██╗
╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██╔═══██╗████╗  ██║██║
 ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║   ██║██╔██╗ ██║██║
  ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║   ██║██║╚██╗██║╚═╝
   ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝╚██████╔╝██║ ╚████║██╗
   ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═══╝╚═╝)" 
              << termcolor::reset << std::endl;
}

// Destructor: Cleans up dynamically allocated memory
/**
 * @brief Destructor for the Game class.
 * 
 * @details 
 * Deallocates all dynamically allocated memory, including the labyrinth, player, minotaur, and items,
 * to prevent memory leaks.
 */
Game::~Game()
{
    // Delete dynamically allocated objects to prevent memory leaks
    delete labyrinth;
    delete player;
    delete minotaur;

    // Iterate through the items list and delete each item
    for (auto it = items.begin(); it != items.end(); ++it) {
        delete *it;
    }
}