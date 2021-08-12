#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>
#include "tile.h"

class Board {
    std::vector<Tile> tiles;  // vector list of tiles on board

   public:
    // initialize the board
    void initBoard(int *resources, int *tileValues);
    void printBoard();  // display the board

    // testing functions
    void displayTile();
    void displayConnections();
    bool buildRoad(int location, int builder);
    bool buildResidence(int location, int builder);
    int vertexToTile(int vertexLocation);
    int edgeToTile(int edgeLocation);
};

#endif