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
        std::cerr << "Opening files neighbours.txt failed." << std::endl;
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

void Board::setSeed(std::default_random_engine _rng) { seed = _rng; }

void Board::initSelection(int mode, std::string fileName) {
    if (mode == 3) {
        std::vector<int> tileValueList = {2,  12, 7, 3, 4, 5, 6, 8,  9, 10,
                                          11, 3,  4, 5, 6, 8, 9, 10, 11};
        for (int i = 0; i < 19; i++) {
            std::shuffle(tileValueList.begin(), tileValueList.end(), seed);
            tileValues.emplace_back(tileValueList[0]);
            tileValueList.erase(tileValueList.begin());
        }

        std::vector<int> typeList = {4, 4, 4, 3, 3, 3, 0, 0, 0, 0,
                                     1, 1, 1, 1, 2, 2, 2, 2, 5};
        for (int i = 0; i < 19; i++) {
            std::shuffle(typeList.begin(), typeList.end(), seed);
            resources.emplace_back(typeList[0]);
            typeList.erase(typeList.begin());
        }

        defaultInitBoard();

    } else if (mode == 2 || mode == 4 || mode == 1) {
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

bool Board::checkCanBuildResAt(int location, int builder, bool first) {
    if (!allVertices[location]->getCanBuildResidence()) return false;

    if (first) return true;

    std::vector<int> neigherEdge = allVertices[location]->getEdgeNeighbours();

    for (auto index : neigherEdge)
        if (allEdges[index]->getWhichBuilder() == builder) return true;

    return false;
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

bool Board::checkCanBuildRoadAt(int colour, int location) {
    if (allEdges[location]->getHasRoad()) return false;
    std::vector<int> nbrVertices = allEdges[location]->getVerticesNeighbours();
    for (auto eachVertex : nbrVertices) {
        if (allVertices[eachVertex]->getWhichBuilder() == colour) {
            return true;  // if one of the neighbour vertices is the same colour
        } else if (allVertices[eachVertex]->getWhichBuilder() != -1) {
            continue;
        } else {
            // iterate through every neighbour edges to see if we have a
            // neighbour road
            std::vector<int> nbrEdge =
                allVertices[eachVertex]->getEdgeNeighbours();
            for (auto eachEdge : nbrEdge) {
                if (allEdges[eachEdge]->getWhichBuilder() == colour &&
                    allEdges[eachEdge]->getLocation() != location) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::buildRoadAt(int colour, int location) {
    allEdges[location]->setHasRoad(true);
    allEdges[location]->setWhichBuilder(colour);
}

std::vector<int> Board::getResLocOnTile(int location) {
    std::vector<int> resOnLocOnTile;
    std::vector<int> verticesOnTile = tiles[location].getTheVertices();
    for (int i : verticesOnTile) {
        if (allVertices[i]->getWhichBuilder() != -1) {
            resOnLocOnTile.emplace_back(i);
        }
    }
    return resOnLocOnTile;
}

std::string Board::getBoardData() {
    std::string data = "";
    for (size_t i = 0; i < tiles.size(); i++) data += tiles[i].getData() + " ";
    return data;
}

void Board::clearBoard() {
    // clear tiles
    for (auto eachTile : tiles) {
        eachTile.clearTile();
    }
    // clear vertices
    for (auto eachVertex : allVertices) {
        eachVertex->clearVertex();
    }
    // clear edges
    for (auto eachEdge : allEdges) {
        eachEdge->clearEdge();
    }
}

void Board::addRoadRelation(int builder, std::vector<int> lst) {
    for (auto num : lst) {
        allEdges[num]->setHasRoad(true);
        allEdges[num]->setWhichBuilder(builder);
    }
}

void Board::addResidenceRelation(int builder, std::vector<int> lst) {
    for (auto num : lst) buildResAt(num, builder);
}