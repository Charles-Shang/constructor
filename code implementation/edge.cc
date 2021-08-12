#include "edge.h"
#include <iostream>

Edge::Edge(int _location, bool _hasRoad, int _whichBuilder)
    : location{_location}, hasRoad{_hasRoad}, whichBuilder{_whichBuilder} {}

void Edge::addVerticeNeighbour(const std::shared_ptr<Vertices> &vertice) {
    connectedVertices.emplace_back(vertice);
}

int Edge::getLocation() { return location; }

void Edge::displayNeighbourVertices() {
    std::cout << "Edge: " << location << "" << std::endl;
    std::cout << "Connected Vertices are: " << std::endl;
    for (size_t i = 0; i < connectedVertices.size(); i++) {
        std::cout << connectedVertices[i]->getLocation() << " ";
    }
    std::cout << std::endl;
}

bool Edge::addRoad(int builder) {
    if (!hasRoad) {
        hasRoad = true;
        whichBuilder = builder;
    } else {
        return false;
    }
}

// 这个还没完善，得检查是不是真的可以
bool Edge::checkCanBuildRoad(int color) {

    if (hasRoad) return false;


    


    return true;
}