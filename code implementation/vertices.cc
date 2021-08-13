#include "vertices.h"
#include <iostream>

Vertices::Vertices(int _location, bool _canBuildRes, int _whichBuilder)
    : location{_location},
      canBuildResidence{_canBuildRes},
      whichBuilder{_whichBuilder} {}

void Vertices::addEdgeNeighbour(const int &edge) {
    connectedEdges.emplace_back(edge);
}

bool Vertices::getCanBuildResidence() { return canBuildResidence; }

void Vertices::buildRes(int builder) {
    canBuildResidence = false;
    whichBuilder = builder;
}

std::vector<int> Vertices::getEdgeNeighbours() { return connectedEdges; }

void Vertices::setCannotBuild() { canBuildResidence = false; }

int Vertices::getWhichBuilder() { return whichBuilder; }

int Vertices::getLocation() { return location; }
