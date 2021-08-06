#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include "tile.h"

class Board {
    std::vector<Tile> tiles;

   public:
    void initBoard();   // initialize the board
    void printBoard();  // display the board
};

#endif