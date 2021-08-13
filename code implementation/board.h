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
    void initSelection(int mode, std::string fileName = "layout.txt");
    void setupVerticesAndEdgesRelation();

    bool checkCanBuildResAt(int location, int builder, bool first = false);
    void buildResAt(int location, int builder);

    bool checkCanBuildRoadAt(int location);

    std::string getTileTypeAtLocation(int location);
    int getTileValueAtLocation(int location);
    bool getTileHasGeeseAtLocation(int location);

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
};

#endif