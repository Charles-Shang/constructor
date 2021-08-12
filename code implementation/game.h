#ifndef _GAME_H_
#define _GAME_H_

#include <random>
#include <vector>
#include "board.h"
#include "builder.h"

class Game {
    Board thisBoard;  // the board in the game
    std::vector<Builder> allPlayers;
    std::default_random_engine seed;
    int curTurn;

   public:
    void initializeGame(int inputMode, std::string fileName,
                        std::default_random_engine _rng);
    void play();       // start the Game of Constructor
    void printHelp();  // display help command message
    void beginTurn();  // start a round for a player
    void duringTheTurn();
    void beginGame();
    void moveGeese();
    void gainResources(int diceResult);
    // testing
    void newMain();
    void saveGame();
};

#endif