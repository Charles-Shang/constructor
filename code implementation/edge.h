#ifndef _EDGE_H_
#define _EDGE_H_

#include <memory>
#include <vector>
#include "vertices.h"

class Vertices;

class Edge {
    int location;      // location on the board
    bool hasRoad;      // truth value for whether a road is built
    bool canBuildRoad;
    int whichBuilder;  // which builder built the road
    // vector list of shared pointer of vertices that are neighbours of edge
    std::vector<std::shared_ptr<Vertices>> connectedVertices;

   public:
    // initially -1 represent no road
    Edge(int _location, bool _hasRoad = false, int _whichBuilder = -1);
    bool addRoad(int builder);  // build a road at the location of the edge
    // produce the truth value of whether a builder can build a road at location
    bool checkCanBuildRoad();
    // add edge neighbours of vertices
    void addVerticeNeighbour(const std::shared_ptr<Vertices> &vertice);

    // testing functions
    int getLocation();
    void displayNeighbourVertices();
};

#endif