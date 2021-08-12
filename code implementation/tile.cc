#include "tile.h"

// temp testings
#include <iostream>

void Tile::initTile() {}
Tile::Tile(int _type, int _tileNum, int _tileValue, int _load)
    : type{_type}, tileNum{_tileNum}, tileValue{_tileValue} {
    if (_load == 0)
        hasGeese = _type == 5 ? true : false;
    else if (_load == 1)
        hasGeese = true;
    else
        hasGeese = false;
}

std::string Tile::getTileType() {
    switch (type) {
        case 0:
            return "BRICK";
        case 1:
            return "ENERGY";
        case 2:
            return "GLASS";
        case 3:
            return "HEAT";
        case 4:
            return "WIFI";
        default:
            return "PARK";
    }
}

int Tile::getTileValue() { return tileValue; }

bool Tile::getHasGeese() { return hasGeese; }

void Tile::addVertices(const std::shared_ptr<Vertices> &vertice) {
    theVertices.emplace_back(vertice);
}

void Tile::addEdge(const std::shared_ptr<Edge> &edge) {
    theEdges.emplace_back(edge);
}

void Tile::displayVNE() {
    std::cout << (tileNum < 10 ? " " : "") << tileNum << " ";
    for (int i = 0; i < 6; i++) {
        int a = theVertices[i]->getLocation();
        std::cout << (a < 10 ? " " : "") << a << " ";
    }

    for (int i = 0; i < 6; i++) {
        int a = theEdges[i]->getLocation();
        std::cout << (a < 10 ? " " : "") << a << " ";
    }
    std::cout << std::endl;
}

void Tile::displayConnections() {
    for (int i = 0; i < 6; i++) {
        theVertices[i]->displayNeighbourEdges();
    }

    for (int i = 0; i < 6; i++) {
        theEdges[i]->displayNeighbourVertices();
    }
}

bool Tile::addRoad(int location, int builder) {
    auto toBeBuilt = theEdges[location];
    if (toBeBuilt->checkCanBuildRoad(builder)) {
        toBeBuilt->addRoad(builder);
        return true;
    } else {
        return false;
    }
}

bool Tile::addResidence(int location, int builder) {
    auto toBeBuilt = theVertices[location];
    if (toBeBuilt->checkCanBuildResidence()) {
        toBeBuilt->addResidence(builder);
        return true;
    } else {
        return false;
    }
}

std::string Tile::getData() {
    std::string data = "";
    data = std::to_string(type) + " " + std::to_string(tileValue);
    return data;
}

int Tile::getType() { return type; }

std::vector<int> Tile::playersResources() {
    std::vector<int> players;
    for (auto vertex : theVertices) {
        if (vertex->getWhichBuilder() != -1) {
            players.emplace_back(vertex->getWhichBuilder());
        }
    }
    return players;
}