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

void Board::initBoard(int *resources, int *tileValues) {
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

// format tile's value with approporiate spacing and output to standard output
void printTileType(std::string tileTypeName) {
    std::string blank = "   ";
    std::cout << tileTypeName << blank.substr(0, 6 - tileTypeName.size());
}

// format tile's type with approporiate spacing and output to standard output
void printTileValue(int tileValue) {
    if (tileValue < 10) std::cout << " ";
    std::cout << tileValue;
}

// display the board
void Board::printBoard() {
    std::ifstream boardFile;

    try {
        boardFile = std::ifstream{"boardTemplate.txt"};
    } catch (const std::exception &e) {
        std::cerr << "Opening file boardTemplate.txt failed." << std::endl;
    }

    int typeCount = 0, valueCount = 0, geeseCount = 0;
    char c;

    while (true) {
        boardFile >> c;
        if (boardFile.eof()) break;

        if (c == 'T') {  // T for Type
            boardFile >> c >> c >> c >> c >> c;
            printTileType(tiles[typeCount++].getTileType());
        } else if (c == 'V') {  // V for Value
            boardFile >> c;
            printTileValue(tiles[valueCount++].getTileValue());
        } else if (c == 'G') {  // G for Geese
            boardFile >> c >> c >> c >> c >> c;
            if (!tiles[geeseCount++].getHasGeese()) {
                std::cout << "      ";
            } else {
                std::cout << "GEESE ";
            }
        } else if (c == ',') {  // , for new line
            std::cout << std::endl;
        } else if (c == '_') {  // _ for space
            std::cout << " ";
        } else {
            std::cout << c;
        }
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
