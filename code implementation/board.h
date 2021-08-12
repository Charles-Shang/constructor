#ifndef _BOARD_H_
#define _BOARD_H_

#include <map>
#include <vector>
#include "tile.h"

class Board {
    std::vector<Tile> tiles;  // vector list of tiles on board
    std::map<int, std::vector<int>> verticeMap;
    std::map<int, std::vector<int>> edgeMap;

   public:
    // initialize the board
    void defaultInitBoard(int *resources, int *tileValues);
    void printBoard();  // display the board

    // testing functions
    void displayTile();
    void displayConnections();
    bool buildRoad(int location, int builder);
    bool buildRes(int location, int builder);
    int vertexToTile(int vertexLocation);
    int edgeToTile(int edgeLocation);
};

#endif