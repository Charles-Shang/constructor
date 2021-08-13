#include "vertices.h"
#include <iostream>

Vertices::Vertices(int _location, bool _canBuildResidence, int _whichBuilder)
    : location{_location},
      canBuildResidence{_canBuildResidence},
      whichBuilder{_whichBuilder} {}

// assume can build
void Vertices::addResidence(int builder) {
    std::cout << "Res added successfully at location " << location << " ";
    std::cout << "Builder is " << builder << std::endl;
    canBuildResidence = false;
    whichBuilder = builder;
    notifyNeighbours();
}

void Vertices::addEdgeNeighbour(const std::shared_ptr<Edge> &edge) {
    connectedEdges.emplace_back(edge);
}

int Vertices::getLocation() { return location; }

void Vertices::displayNeighbourEdges() {
    std::cout << "Vertice: |" << location << "|" << std::endl;
    std::cout << "Connected edges are: " << std::endl;
    for (size_t i = 0; i < connectedEdges.size(); i++)
        std::cout << connectedEdges[i]->getLocation() << " ";

    std::cout << std::endl;
}

bool Vertices::checkCanBuildResidence() { return canBuildResidence; }

void Vertices::notifyNeighbours() {
    for (auto single : connectedEdges) single->turnOffNeighbourVertices();
}

std::vector<std::shared_ptr<Edge>> &Vertices::getConnectedEdges() {
    return connectedEdges;
}

int Vertices::getWhichBuilder() { return whichBuilder; }

void Vertices::setCannotBuildRes() {
    std::cout << "Vertice NOW cannot be built at location " << location;
    std::cout << std::endl;
    canBuildResidence = false;
}