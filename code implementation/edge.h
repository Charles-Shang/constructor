#ifndef _EDGE_H_
#define _EDGE_H_

#include <memory>
#include <vector>
#include "vertices.h"

class Edge {
    int location;       // location on the board
    bool hasRoad;       // truth value for whether a road is built
    int whichBuilder;   // which builder built the road
    // vector list of shared pointer of vertices that are neighbours of edge
    std::vector<std::shared_ptr<Vertices>> neighbourResidence;

   public:
    void addRoad(); // build a road at the location of the edge
    // produce the truth value of whether a builder can build a road at location
    bool canBuildRoad(); 
};

#endif