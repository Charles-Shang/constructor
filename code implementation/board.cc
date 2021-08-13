#include "board.h"
#include <algorithm>
#include <fstream>
#include <iostream>

void Board::setupVerticesAndEdgesRelation() {
    int location;
    std::ifstream neighbourFile;

    try {
        neighbourFile = std::ifstream{"neighbours.txt"};
    } catch (const std::exception &e) {
        std::cerr << "Opening files neighbours.txt or failed." << std::endl;
    }

    const int delimiter = 999;
    for (int j = 0; j < totalVertices; j++) {
        std::shared_ptr<Vertices> vertix = std::make_shared<Vertices>(j);
        allVertices.emplace_back(vertix);
    }

    for (int j = 0; j < totalEdges; j++) {
        std::shared_ptr<Edge> edge = std::make_shared<Edge>(j);
        allEdges.emplace_back(edge);
    }

    for (int j = 0; j < totalVertices; j++) {
        neighbourFile >> location;
        while (true) {
            neighbourFile >> location;
            if (location == delimiter) break;
            allVertices[j]->addEdgeNeighbour(location);
        }
    }

    for (int j = 0; j < totalEdges; j++) {
        neighbourFile >> location;
        while (true) {
            neighbourFile >> location;
            if (location == delimiter) break;
            allEdges[j]->addVerticeNeighbour(location);
        }
    }
}

void Board::init(int mode, std::string fileName) {
    if (mode == 4) {
        std::ifstream layoutFile;

        try {
            layoutFile = std::ifstream{fileName};
        } catch (const std::exception &e) {
            std::cerr << "Opening file " << fileName << "failed." << std::endl;
        }

        int num;

        for (int i = 0; i < 19; i++) {
            layoutFile >> num;
            if (layoutFile.eof()) break;
            resources.emplace_back(num);
            layoutFile >> num;
            tileValues.emplace_back(num);
            ;
        }

        defaultInitBoard();
    }
}

void Board::defaultInitBoard() {
    std::ifstream tileFile;

    try {
        tileFile = std::ifstream{"tileVertices.txt"};
    } catch (const std::exception &e) {
        std::cerr << "Opening file tileVertices.txt failed." << std::endl;
    }
    int location;

    setupVerticesAndEdgesRelation();

    for (int i = 0; i < 19; i++) {
        tileFile >> location;
        Tile theTile{resources[i], i, tileValues[i]};

        // read the vertices of this tile
        for (int vertexNum = 0; vertexNum < 6; ++vertexNum) {
            tileFile >> location;
            theTile.addVertices(location);
            verticeMap[location].emplace_back(i);
        }
        // read the edges of this tile
        for (int edgeNum = 0; edgeNum < 6; ++edgeNum) {
            tileFile >> location;
            theTile.addEdge(location);
            edgeMap[location].emplace_back(i);
        }

        tiles.emplace_back(theTile);
    }
}

bool Board::checkCanBuildResAt(int location) {
    return allVertices[location]->getCanBuildResidence();
}

// note: it also notifies the neighbours
void Board::buildResAt(int location, int builder) {
    allVertices[location]->buildRes(builder);
    for (auto i : allVertices[location]->getEdgeNeighbours())
        for (auto j : allEdges[i]->getVerticesNeighbours())
            allVertices[j]->setCannotBuild();
}

std::string Board::getTileTypeAtLocation(int location) {
    return tiles[location].getTileType();
}

int Board::getTileValueAtLocation(int location) {
    return tiles[location].getTileValue();
}

bool Board::getTileHasGeeseAtLocation(int location) {
    return tiles[location].getHasGeese();
}

int Board::whichHasGeese() {
    for (size_t i = 0; i < tiles.size(); i++)
        if (tiles[i].getHasGeese()) return i;
    return 99999;  // this should never reach
}

void Board::transferGeese(int current, int destination) {
    tiles[current].updateGeese(false);
    tiles[destination].updateGeese(true);
}

std::vector<int> Board::getPlayersOnTile(int location, bool nonRepeat) {
    std::vector<int> tileVertices = tiles[location].getTheVertices();
    std::vector<int> players;
    for (auto vertexLocation : tileVertices) {
        int builderNum = allVertices[vertexLocation]->getWhichBuilder();
        if (builderNum != -1) players.emplace_back(builderNum);
    }

    if (nonRepeat) {
        std::sort(players.begin(), players.end());
        players.erase(std::unique(players.begin(), players.end()),
                      players.end());
    }

    return players;
}

std::vector<int> Board::tileValToNum(int tileValue) {
    std::vector<int> tileNums;
    for (auto tile : tiles) {
        if (tile.getTileValue() == tileValue) {
            tileNums.emplace_back(tile.getTileNum());
        }
    }
    return tileNums;
}

int Board::getRssOnTile(int curTile) { return tiles[curTile].getTileTypeNum(); }