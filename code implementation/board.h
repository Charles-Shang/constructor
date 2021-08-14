#ifndef _BOARD_H_
#define _BOARD_H_

#include <map>
#include <memory>
#include <random>
#include <vector>
#include "edge.h"
#include "tile.h"
#include "vertices.h"

class Board {
    std::default_random_engine seed;
    std::vector<Tile> tiles;  // vector list of tiles on board
    std::map<int, std::vector<int>> verticeMap;  // map vertices to tiles
    std::map<int, std::vector<int>> edgeMap;     // map edges to tile
    std::vector<std::shared_ptr<Vertices>>
        allVertices;                              // all vertices in the board
    std::vector<std::shared_ptr<Edge>> allEdges;  // all edges in the board
    std::vector<int> resources;                   // resources in each tile
    std::vector<int> tileValues;                  // tile values in each tile

    // constants
    const int totalVertices = 54;
    const int totalEdges = 72;

    void defaultInitBoard();

   public:
    // initialize the board
    void initSelection(int mode, std::string fileName = "layout.txt");
    void setupVerticesAndEdgesRelation();

    // check if we can build residence or road at location of builder
    bool checkCanBuildResAt(int location, int builder, bool first = false);
    void buildResAt(int location, int builder);

    bool checkCanBuildRoadAt(int location);

    // getters
    std::string getTileTypeAtLocation(int location);
    int getTileValueAtLocation(int location);
    bool getTileHasGeeseAtLocation(int location);

    // returns which tile has the geese
    int whichHasGeese();
    void transferGeese(int current, int destination);

    // assume returned vector list is sorted and unique
    std::vector<int> getPlayersOnTile(int location, bool nonRepeat = true);

    bool checkCanBuildRoadAt(int colour, int location);
    void buildRoadAt(int colour, int location);

    // use for gain resource
    std::vector<int> tileValToNum(int tileValue);
    int getRssOnTile(int curTile);
    std::vector<int> getResLocOnTile(int location);

    std::string getBoardData();  // in layout.txt format
    void clearBoard();

    void setSeed(std::default_random_engine _rng);

    void addRoadRelation(int builder, std::vector<int> lst);
    void addResidenceRelation(int builder, std::vector<int> lst);
};

#endif
