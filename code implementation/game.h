#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include "board.h"
#include "builder.h"

class Game {
    Board thisBoard;  // the board in the game
    unsigned seed;

   public:
    void initializeGame(int inputMode, std::string fileName, unsigned _seed);
    void play();                         // start the Game of Constructor
    void printHelp();                    // display help command message
    void beginTurn(Builder &curPlayer);  // start a round for a player
    void duringTheTurn(Builder &curPlayer, std::vector<Builder> &allPlayers);
    void beginGame(std::vector<Builder> &allPlayers);
    // testing
    void newMain();
};

#endif