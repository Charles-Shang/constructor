#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include "tile.h"

class Board {
    std::vector<Tile> tiles; // vector list of tiles on board
    const int tileSize = 19; // total tiles contained 

   public:
    // initialize the board
    void initBoard(int *resources, int *tileValues);
    void printBoard();  // display the board
};

#endif