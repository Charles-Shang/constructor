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
    void duringTheTurn();
    void printBoard();
    std::string builtInWhichColour(int location, std::string type);

    void moveGeese();
    void gainResources(int diceResult);
    void printHelp();  // display help command message
    void saveGame();

   public:
    Game(std::default_random_engine _rng);
    void initializeGame(int inputMode, std::string fileName);
    bool play();  // start the Game of Constructor
    void newMain();
    void clearAll();

    
};

#endif