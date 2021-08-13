#ifndef _EDGE_H_
#define _EDGE_H_

#include <vector>

class Edge {
    int location;      // location on the board
    bool hasRoad;      // truth value for whether a road is built
    int whichBuilder;  // which builder built the road
    // vector list of shared pointer of vertices that are neighbours of edge
    std::vector<int> connectedVertices;

   public:
    // initially -1 represent no road
    Edge(int _location, bool _hasRoad = false, int _whichBuilder = -1);
    void addVerticeNeighbour(const int &vertice);

    std::vector<int> getVerticesNeighbours();
    bool getHasRoad();
    int getWhichBuilder();
    int getLocation();
    void setHasRoad(bool hasRd);
    void setWhichBuilder(int colour);
    void clearEdge();


    
};

#endif