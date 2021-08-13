#include "tile.h"
#include <iostream>

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

void Tile::addVertices(int vertice) { theVertices.emplace_back(vertice); }

void Tile::addEdge(int edge) { theEdges.emplace_back(edge); }

void Tile::updateGeese(bool state) { hasGeese = state; }

std::vector<int> Tile::getTheVertices() { return theVertices; }

int Tile::getTileNum() { return tileNum; }

int Tile::getTileTypeNum() { return type; }

std::string Tile::getData() {
    std::string data = "";
    data = std::to_string(type) + " " + std::to_string(tileValue);
    return data;
}
