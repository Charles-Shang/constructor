#include "tile.h"

// temp testings
#include <iostream>

void Tile::initTile() {

}
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
        default:  // "5"
            return "PARK";
    }
}

int Tile::getTileValue() { return tileValue; }

bool Tile::getHasGeese() { return hasGeese; }

void Tile::addVertices(int location) {
    Vertices v{location};
    theVertices.emplace_back(&v);
}

void Tile::addEdge(int location) {
    Edge e{location};
    theEdges.emplace_back(&e);
}