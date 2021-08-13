#ifndef _VERTICES_H_
#define _VERTICES_H_

#include <vector>

class Vertices {
    int location;  // location on the board
    // truth value of whether a residence can build at the location
    bool canBuildResidence;
    int whichBuilder;  // the owner of the residence
    // vector list of shared pointer of edges that are neighbours of vertice
    std::vector<int> connectedEdges;

   public:
    // initially -1 represent no residence
    Vertices(int _location, bool _canBuildRes = true, int _whichBuilder = -1);
    void addEdgeNeighbour(const int &edge);

    bool getCanBuildResidence();
    void buildRes(int builder);

    std::vector<int> getEdgeNeighbours();

    void setCannotBuild();

    int getWhichBuilder();
};

#endif