#ifndef _TILE_H_
#define _TILE_H_

#include <vector>
#include "edge.h"
#include "tiletype.h"
#include "vertices.h"

class Tile {
    // (0 - Brick, 1 - Energy, 2 - Glass, 3 - Heat, 4 - Wifi, 5 - Park)
    int type;       // the type of the tile
    int tileNum;    // the location (tile name) of the tile
    int tileValue;  // the dice value (tile value) of the tile
    bool hasGeese;  // truth value of whether the geese is on the tile
    // the vertices of the tile
    std::vector<std::shared_ptr<Vertices>> theVertices;
    std::vector<std::shared_ptr<Edge>> theEdges;  // the edges of the tile

   public:
    Tile(int _type, int _tileNum, int _tileValue, int _load = 0);
    void initTile();  // initialize the tile
    std::string getTileType();
    int getTileValue();
    bool getHasGeese();
    void addVertices(const std::shared_ptr<Vertices> &vertice);
    void addEdge(const std::shared_ptr<Edge> &edge);

    // testing function
    void displayVNE();
    void displayConnections();
    
    // bool addRoad(int location, int builder);
    // bool addResidence(int location, int builder);
};

#endif