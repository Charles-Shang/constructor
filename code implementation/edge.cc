#include "edge.h"

Edge::Edge(int _location, bool _hasRoad, int _whichBuilder)
    : location{_location}, hasRoad{_hasRoad}, whichBuilder{_whichBuilder} {}


void Edge::addVerticeNeighbour(const std::shared_ptr<Vertices> &vertice){
    connectedVertices.emplace_back(vertice);
}