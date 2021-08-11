#include "vertices.h"

Vertices::Vertices(int _location, bool _canBuildResidence, int _whichBuilder)
    : location{_location},
      canBuildResidence{_canBuildResidence},
      whichBuilder{_whichBuilder} {}

void Vertices::addResidence(int builder) {
    if (!canBuildResidence) {
        canBuildResidence = false;
    } else {
        std::cout << "cannot build residence at this location" << std::endl;
        return;
    }
    whichBuilder = builder;
}

void Vertices::addEdgeNeighbour(const std::shared_ptr<Edge> &edge) {
    connectedEdges.emplace_back(edge);
}