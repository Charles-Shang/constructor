#include "board.h"
#include <fstream>
#include <iostream>

void setupVerticesAndEdges(std::vector<std::shared_ptr<Vertices>> &allVertices,
                           std::vector<std::shared_ptr<Edge>> &allEdges) {
    const int totalVertices = 54;
    const int totalEdges = 72;
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
            allVertices[j]->addEdgeNeighbour(allEdges[location]);
        }
    }

    for (int j = 0; j < totalEdges; j++) {
        neighbourFile >> location;
        while (true) {
            neighbourFile >> location;
            if (location == delimiter) break;
            allEdges[j]->addVerticeNeighbour(allVertices[location]);
        }
    }
}

void setupVerticesObservers(std::vector<std::shared_ptr<Vertices>> &all) {
    for (size_t i = 0; i < all.size(); i++) all[i]->attachALL();
}

void Board::defaultInitBoard(int *resources, int *tileValues) {
    std::ifstream tileFile;

    try {
        tileFile = std::ifstream{"tileVertices.txt"};
    } catch (const std::exception &e) {
        std::cerr << "Opening file tileVertices.txt failed." << std::endl;
    }
    int location;

    // create all vertices and edges pointers
    std::vector<std::shared_ptr<Vertices>> allVertices;
    std::vector<std::shared_ptr<Edge>> allEdges;
    setupVerticesAndEdges(allVertices, allEdges);
    setupVerticesObservers(allVertices);

    for (int i = 0; i < 19; i++) {
        tileFile >> location;
        // add resources and values to tile
        Tile theTile{resources[i], i, tileValues[i]};

        // read the vertices of this tile
        for (int vertexNum = 0; vertexNum < 6; ++vertexNum) {
            tileFile >> location;
            theTile.addVertices(allVertices[location]);
            verticeMap[location].emplace_back(i);
        }
        // read the edges of this tile
        for (int edgeNum = 0; edgeNum < 6; ++edgeNum) {
            tileFile >> location;
            theTile.addEdge(allEdges[location]);
            edgeMap[location].emplace_back(i);
        }

        tiles.emplace_back(theTile);
    }
}

void Board::displayTile() {
    for (int i = 0; i < 19; i++) {
        tiles[i].displayVNE();
    }
}

void Board::displayConnections() {
    for (int i = 0; i < 19; i++) {
        tiles[i].displayConnections();
    }
}

bool Board::buildRes(int location, int builder) {
    int tileNum = vertexToTile(location);
    return tiles[tileNum].addResidence(location, builder);
}

bool Board::buildRoad(int location, int builder) {
    int tileNum = edgeToTile(location);
    return tiles[tileNum].addRoad(location, builder);
}

int Board::vertexToTile(int vertexLocation) {
    return verticeMap[vertexLocation].front();
}

int Board::edgeToTile(int edgeLocation) {
    return edgeMap[edgeLocation].front();
}

std::string Board::getBoardData() {
    std::string data = "";
    for (size_t i = 0; i < tiles.size(); i++) data += tiles[i].getData() + "";
    return data;
}

int Board::whichHasGeese() {
    for (size_t i = 0; i < tiles.size(); i++)
        if (tiles[i].getHasGeese()) return i;
    return 99999;  // this should never reach
}

int Board::getRssOnTile(int tileNum) { return tiles[tileNum].getType(); }

std::vector<int> Board::getPlayersOnTile(int location) {
    return tiles[location].getAllPlayOnTheTile();
}
std::vector<int> Board::getResLocOnTile(int location) {
    return tiles[location].getResLocOnTheTile();
}

void Board::transferGeese(int current, int destination) {
    tiles[current].updateGeese(false);
    tiles[destination].updateGeese(true);
}

std::vector<int> Board::tileValToNum(int value) {
    std::vector<int> tileNums;
    for (auto eachTile : tiles) {
        if (eachTile.getTileValue() == value) {
            tileNums.emplace_back(eachTile.getTileNum());
        }
    }
    return tileNums;
}

int Board::getTileValueAtLocation(int location) {
    return tiles[location].getTileValue();
}

std::string Board::getTileTypeAtLocation(int location) {
    return tiles[location].getTileType();
}

bool Board::getTileHasGeeseAtLocation(int location) {
    return tiles[location].getHasGeese();
}