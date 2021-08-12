#ifndef _GAME_H_
#define _GAME_H_

#include <vector>
#include "board.h"
#include "builder.h"

class Game {
    Board thisBoard;  // the board in the game
    std::vector<Builder> allPlayers;
    unsigned seed;
    int curTurn;

   public:
    void initializeGame(int inputMode, std::string fileName, unsigned _seed);
    void play();                         // start the Game of Constructor
    void printHelp();                    // display help command message
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