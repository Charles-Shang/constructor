#include "tile.h"

// temp testings
#include <iostream>

Tile::Tile(int _type, int _tileNum, int _tileValue)
    : type{_type}, tileNum{_tileNum}, tileValue{_tileValue} {
    hasGeese = _type == 5 ? true : false;
}

std::string getTypeName(int num) {
    switch (num) {
        case 0:
            return "Brick";
        case 1:
            return "Energy";
        case 2:
            return "Glass";
        case 3:
            return "Heat";
        case 4:
            return "Wifi";
        default:  // "5"
            return "Park";
    }
}

std::string Tile::printTile() {

    std::string name = std::to_string(tileNum) + "   ";
    name += getTypeName(type) + "   ";
    name += std::to_string(tileValue);
    if (type == 5) name += " true";

    return name;
}