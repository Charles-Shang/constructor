#ifndef _BOARD_H_
#define _BOARD_H_

#include <map>
#include <vector>
#include <memory>
#include "tile.h"
#include "vertices.h"
#include "edge.h"

class Board {
    std::vector<Tile> tiles;  // vector list of tiles on board
    std::map<int, std::vector<int>> verticeMap;
    std::map<int, std::vector<int>> edgeMap;
    std::vector<std::shared_ptr<Vertices>> allVertices;
    std::vector<std::shared_ptr<Edge>> allEdges;
    std::vector<int> resources;
    std::vector<int> tileValues;

    const int totalVertices = 54;
    const int totalEdges = 72;

    void defaultInitBoard();

   public:
    // initialize the board
    void init(int mode, std::string fileName = "layout.txt");
    void setupVerticesAndEdgesRelation();
    
    bool checkCanBuildResAt(int location);
    void buildResAt(int location, int builder);

    std::string getTileTypeAtLocation(int location);
    int getTileValueAtLocation(int location);
    bool getTileHasGeeseAtLocation(int location);
    
    int whichHasGeese();

};

#endif