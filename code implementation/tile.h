#ifndef _TILE_H_
#define _TILE_H_

#include <vector>
//#include "vertices.h"
//#include "edge.h"
#include "tiletype.h"

// ---------temp use----------
#include <string>
// ---------------------------

class Tile {
    // (0 - Brick, 1 - Energy, 2 - Glass, 3 - Heat, 4 - Wifi, 5 - Park)
    int type;       // the type of the tile
    int tileNum;    // the location (tile name) of the tile
    int tileValue;  // the dice value (tile value) of the tile
    bool hasGeese;  // truth value of whether the geese is on the tile
    // std::vector<std::shared_ptr<Vertices>> theVertices;  // the vertices of the tile
    // std::vector<std::shared_ptr<Edges>> theEdges;  // the edges of the tile

   public:
    void initTile();  // initialize the tile

    // temp test functions
    Tile(int _type, int _tileNum, int _tileValue, int _load = 0);
    std::string getTileType();
    int getTileValue();
    bool getHasGeese();
};

#endif