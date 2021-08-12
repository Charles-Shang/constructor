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

bool Edge::checkCanBuildRoad(int colour) {
    if (hasRoad) return false;
    for (auto nbrVertices : connectedVertices) {
        if (nbrVertices->getWhichBuilder() == colour) {
            return true;  // if one of the neighbour vertices is the same colour
        } else {
            for (auto nbrVertices : connectedVertices) {
                for (auto nbrEdges : nbrVertices->getConnectedEdges()) {
                    if (nbrEdges->getWhichBuilder() == whichBuilder &&
                        nbrEdges->getLocation() != location) {
                        if ((nbrVertices->getWhichBuilder() == -1) ||
                            nbrVertices->getWhichBuilder() == whichBuilder) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}


int Edge::getWhichBuilder() { return whichBuilder; }