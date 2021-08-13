#include "edge.h"
#include <iostream>

Edge::Edge(int _location, bool _hasRoad, int _whichBuilder)
    : location{_location}, hasRoad{_hasRoad}, whichBuilder{_whichBuilder} {}

void Edge::addVerticeNeighbour(const int &vertice) {
    connectedVertices.emplace_back(vertice);
}

std::vector<int> Edge::getVerticesNeighbours() { return connectedVertices; }

bool Edge::getHasRoad() { return hasRoad; }

int Edge::getWhichBuilder() { return whichBuilder; }

int Edge::getLocation() { return location; }

void Edge::setHasRoad(bool hasRd) { hasRoad = hasRd; }

void Edge::setWhichBuilder(int colour) { whichBuilder = colour; }
