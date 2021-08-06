#ifndef _TILE_H_
#define _TILE_H_

#include <vector>
#include "vertices.h"
#include "tiletype.h"

class Tile {
    // (0 - Brick, 1 - Energy, 2 - Glass, 3 - Heat, 4 - Wifi, 5 - Park)
    int type;       // the type of the tile
    int tileNum;    // the location (tile name) of the tile
    int tileValue;  // the dice value (tile value) of the tile
    bool hasGeese;  // truth value of whether the geese is on the tile
    std::vector<Vertices> theVertices;  // the vertices of the tile

   public:
    void initTile();  // initialize the tile
};

#endif