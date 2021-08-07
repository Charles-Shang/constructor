#include "board.h"
#include <fstream>
#include <iostream>

void Board::initBoard(int *resources, int *tileValues) {
    for (int i = 0; i < 19; i++) {
        Tile theTile{resources[i], i, tileValues[i]};
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

        if (c == 'T') { // T for Type
            boardFile >> c >> c >> c >> c >> c;
            printTileType(tiles[typeCount++].getTileType());
        } else if (c == 'V') { // V for Value
            boardFile >> c;
            printTileValue(tiles[valueCount++].getTileValue());
        } else if (c == 'G') { // G for Geese
            boardFile >> c >> c >> c >> c;
            std::cout << tiles[geeseCount++].getHasGeese() ? "GEESE" : "     ";
        } else if (c == ',') { // , for new line
            std::cout << std::endl;
        } else if (c == '_') { // _ for space
            std::cout << " ";
        } else {
            std::cout << c;
        }
    }
}
