#include "tile.h"

// temp testings
#include <iostream>

Tile::Tile(int _type, int _tileNum, int _tileValue)
    : type{_type}, tileNum{_tileNum}, tileValue{_tileValue} {
    hasGeese = _type == 5 ? true : false;
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