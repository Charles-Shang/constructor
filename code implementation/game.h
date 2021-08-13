#ifndef _GAME_H_
#define _GAME_H_

#include <random>
#include <vector>
#include "board.h"
#include "builder.h"

class Game {
    std::default_random_engine seed;
    Board thisBoard;  // the board in the game
    std::vector<std::shared_ptr<Builder>> allPlayers;
    int curPlayer;

    // functions:
    void beginGame();
    void beginTurn();
    void afterTurn();

    void displayBoard();
    std::string builtInWhichColour(int location, std::string type);

   public:
    Game(std::default_random_engine _rng);
    void initializeGame(int inputMode, std::string fileName);
    void play();  // start the Game of Constructor
    void newMain();
};

#endif