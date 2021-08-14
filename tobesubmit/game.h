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
    void beginGame();      // start a game
    void beginTurn();      // begin a turn
    void duringTheTurn();  // during the turn
    void printBoard();     // print the board
    std::string builtInWhichColour(int location, std::string type);

    void moveGeese();                    // move the geese when needed
    void gainResources(int diceResult);  // gain resources on dice result
    void printHelp();                    // display help command message
    void saveGame(bool backup = false);  // save the game

   public:
    Game(std::default_random_engine _rng);
    void initializeGame(int inputMode, std::string fileName);
    bool play(bool load = false);  // start the Game of Constructor
    void clearAll();
};

#endif