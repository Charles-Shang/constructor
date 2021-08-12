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

    // testing functions
    void displayTile();
    void displayConnections();
    bool buildRoad(int location, int builder);
    bool buildRes(int location, int builder);
    int vertexToTile(int vertexLocation);  // get tile number based on vertices
    int edgeToTile(int edgeLocation);
    std::string getBoardData();  // in layout.txt format
    int whichHasGeese();
    int getRssOnTile(int tileNum);
    std::vector<int> getPlayersOnTile(int location);
    std::vector<int> getResLocOnTile(int location);

    void transferGeese(int current, int destination);
    std::vector<int> tileValToNum(int value);

    int getTileValueAtLocation(int location);
    std::string getTileTypeAtLocation(int location);
    bool getTileHasGeeseAtLocation(int location);
};

#endif