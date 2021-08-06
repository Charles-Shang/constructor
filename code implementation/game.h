#ifndef _GAME_H_
#define _GAME_H_

#include <board.h>
#include <vector>
#include "builder.h"

class Game {
    Board thisBoard;                   // the board in the game
    std::vector<Builder> builderList;  // builder (players) list

   public:
    void play();  // start the Game of Constructor
};

#endif