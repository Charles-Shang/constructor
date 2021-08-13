#ifndef _TILE_H_
#define _TILE_H_

#include <vector>
#include <string>

class Tile {
    // (0 - Brick, 1 - Energy, 2 - Glass, 3 - Heat, 4 - Wifi, 5 - Park)
    int type;       // the type of the tile
    int tileNum;    // the location (tile name) of the tile
    int tileValue;  // the dice value (tile value) of the tile
    bool hasGeese;  // truth value of whether the geese is on the tile
    // the vertices of the tile
    std::vector<int> theVertices;
    std::vector<int> theEdges;  // the edges of the tile

   public:
    Tile(int _type, int _tileNum, int _tileValue, int _load = 0);
    std::string getTileType();
    int getTileTypeNum();
    int getTileValue();
    int getTileNum();
    bool getHasGeese();
    void addVertices(int vertice);
    void addEdge(int edge);
    void updateGeese(bool state);
    std::vector<int> getTheVertices();
};

#endif