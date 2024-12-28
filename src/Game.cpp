#include "Game.h"
#include "Labyrinth.h"
#include "Player.h"
#include "Cell.h"
#include "Input.h"
#include "termcolor.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>

Game::Game(unsigned int width, unsigned int height) : logger("game.log"), state(GAME_STATE::PLAYING)
{
    this->init(width, height);
    this->spawn();
    this->labyrinth->print();
    this->updateGameState();
}

void Game::init(unsigned int width, unsigned int height)
{
	
	logger.log("Game init with width: " + std::to_string(width) + " and height: " + std::to_string(height));

    this->labyrinth = new Labyrinth(width, height);

	if (!this->labyrinth->getMapGenerationSuccess()) {
		std::cout << "Try again.\n";
		logger.log("Map generation failed. Exiting...");
		exit(1);
	}
	logger.log("Map generated successfully.");

	logger.log("Start point: " + std::to_string(this->labyrinth->getStartPoint().getRow()) + " " + std::to_string(this->labyrinth->getStartPoint().getCol()));
	logger.log("End point: " + std::to_string(this->labyrinth->getEndPoint().getRow()) + " " + std::to_string(this->labyrinth->getEndPoint().getCol()));

    this->player = new Player();
	this->minotaur = new Minotaur();
}

void Game::spawn()
{
	srand(time(nullptr));
	auto randomNumBetween = [](int min, int max) -> int {
		return min + (rand() % (max - min + 1));
	};

	//Player
    Cell startPoint = this->labyrinth->getStartPoint();
	startPoint.setRow(startPoint.getRow() + 1);
    this->player->setPosition(startPoint);
    this->labyrinth->getCell(startPoint.getRow(), startPoint.getCol()).setVal('R');
	
	logger.log("Player spawned at: " + std::to_string(startPoint.getRow()) + " " + std::to_string(startPoint.getCol()));

	//Minotaur
	//Get a random position in the path
	std::list<Cell*> path = this->labyrinth->getPathFromEntranceToExit();
	int rndPos = randomNumBetween(7, path.size() - 7);
	auto it = path.begin();
	std::advance(it, rndPos);
	Cell* minotaurPos = *it;
	this->minotaur->setPosition(*minotaurPos);
	this->labyrinth->getCell(minotaurPos->getRow(), minotaurPos->getCol()).setVal('M');
	logger.log("Minotaur spawned at: " + std::to_string(minotaurPos->getRow()) + " " + std::to_string(minotaurPos->getCol()));
}	

//
//	Checks if the position is a wall or entrance
//	returns true if it is a wall
//
bool Game::isWall(Cell position) {
	return this->labyrinth->getCell(position.getRow(), position.getCol()).getVal() == '#' ||
		this->labyrinth->getCell(position.getRow(), position.getCol()).getVal() == 'U';
}

void Game::playerMovementUpdate(char command) {
    Cell potential_pos;
    switch (command)
    {
        case 'w':
            potential_pos = Cell(this->player->getPosition().getRow() - 1, this->player->getPosition().getCol(), 'R');
            break;

        case 's':
            potential_pos = Cell(this->player->getPosition().getRow() + 1, this->player->getPosition().getCol(), 'R');
            break;

        case 'a':
            potential_pos = Cell(this->player->getPosition().getRow(), this->player->getPosition().getCol() - 1, 'R');
            break;

        case 'd':
            potential_pos = Cell(this->player->getPosition().getRow(), this->player->getPosition().getCol() + 1, 'R');
            break;

        default:
            return;
    }

    if (!isWall(potential_pos)) {
		this->labyrinth->getCell(
			this->player->getPosition().getRow(),
			this->player->getPosition().getCol()
		).setVal(' ');
        this->player->setPosition(potential_pos);
		this->labyrinth->getCell(
					this->player->getPosition().getRow(),
					this->player->getPosition().getCol()
				).setVal('R');
	}

    logger.log("Action: " + std::string(1, command));
    logger.log("Player moved to: " + std::to_string(this->player->getPosition().getRow()) + " " + std::to_string(this->player->getPosition().getCol()));
}

void Game::minotaurMovementUpdate()
{
    Cell minotaur_pos = this->minotaur->getPosition();

    const int MAX_ATTEMPTS = 4;
    bool moved = false;

	// Make the movement more intelligent
	// The minotaur will not go into direction of the wall twice
	// if he comes across a wall -> he will try to go in another direction
    for (int attempt = 0; attempt < MAX_ATTEMPTS && !moved; ++attempt)
    {
        int randomDirection = rand() % 4;
        Cell potential_pos;

        switch (randomDirection) {
            case 0:
                potential_pos = Cell(minotaur_pos.getRow() - 1, minotaur_pos.getCol(), 'M');
                break;
            case 1:
                potential_pos = Cell(minotaur_pos.getRow() + 1, minotaur_pos.getCol(), 'M');
                break;
            case 2:
                potential_pos = Cell(minotaur_pos.getRow(), minotaur_pos.getCol() - 1, 'M');
                break;
            case 3:
                potential_pos = Cell(minotaur_pos.getRow(), minotaur_pos.getCol() + 1, 'M');
                break;
            default:
                break;
        }

        if (!isWall(potential_pos)) {
            this->labyrinth->getCell(
                this->minotaur->getPosition().getRow(),
                this->minotaur->getPosition().getCol()
            ).setVal(' ');
            this->minotaur->setPosition(potential_pos);
            this->labyrinth->getCell(
                this->minotaur->getPosition().getRow(),
                this->minotaur->getPosition().getCol()
            ).setVal('M');
            moved = true; 
        }

		logger.log("Minotaur moved to: " + std::to_string(this->minotaur->getPosition().getRow()) + " " + std::to_string(this->minotaur->getPosition().getCol()));
    }
}

void Game::checkGameObjectCollision()
{
	
	if (this->player->getPosition() == this->minotaur->getPosition()) 
	{
		state = GAME_STATE::PLAYER_LOST;

		// Make it like Minotaur has eaten the player
		this->labyrinth->getCell(
			this->player->getPosition().getRow(),
			this->player->getPosition().getCol()
		).setVal('M');

		logger.log("Game state updated: " + std::to_string(state));
		return;
	}

	if (this->player->getPosition() == this->labyrinth->getEndPoint())
	{
		state = GAME_STATE::PLAYER_WON;
		logger.log("Game state updated: " + std::to_string(state));
		return;
	}
}

void Game::updateGameState()
{
	logger.log("Game state updated: " + std::to_string(state));
	srand(time(nullptr));
    input::enableRawMode();

	auto lastMinotaurUpdate = std::chrono::steady_clock::now();
    while (state == GAME_STATE::PLAYING)
    {	
		
		//Player movement
        if (input::kbhit()) {
            char command = input::getch();
            
			//command update
			if (command == 'q') {
				state = GAME_STATE::QUIT;
				logger.log("Game state updated: " + std::to_string(state));
			} else {
				playerMovementUpdate(command);
			}

        }
	
		//Minotaur movement
		auto now = std::chrono::steady_clock::now();
        auto diffSec = std::chrono::duration<double>(now - lastMinotaurUpdate).count();

		//change minotaur position every 1 second
        if (diffSec >= 1.0) {
            minotaurMovementUpdate();            
            lastMinotaurUpdate = std::chrono::steady_clock::now();
        }

		checkGameObjectCollision();

		//clear terminal
		system("clear");
		this->labyrinth->print();

		//small delay to low load on cpu
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	//final print
	system("clear");
	this->labyrinth->print();


	switch (state)
	{
	case GAME_STATE::PLAYER_WON:
		printGameWon();
		break;
	case GAME_STATE::PLAYER_LOST:
		printGameOver();
		break;
	default:
		break;

    input::disableRawMode();
	}
}

void Game::printGameOver() {
    std::cout << termcolor::red << termcolor::bold;
    std::cout << R"( ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ 
██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗
██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝
██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗
╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║
 ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝)" << termcolor::reset << std::endl;
}

void Game::printGameWon() {
	std::cout << termcolor::green << termcolor::bold;
	std::cout << R"(██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗ ██████╗ ███╗   ██╗██╗
╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██╔═══██╗████╗  ██║██║
 ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║   ██║██╔██╗ ██║██║
  ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║   ██║██║╚██╗██║╚═╝
   ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝╚██████╔╝██║ ╚████║██╗
   ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═══╝╚═╝)" << termcolor::reset << std::endl;
}

Game::~Game()
{
    delete this->labyrinth;
}