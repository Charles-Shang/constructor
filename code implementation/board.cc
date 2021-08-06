#include "board.h"
#include <iostream>

void Board::initBoard(int *resources, int *tileValues) {
    for (int i = 0; i < tileSize; i++) {
        Tile theTile{resources[i], i, tileValues[i]};
        tiles.emplace_back(theTile);
    }
}

void Board::printBoard() {
    for (Tile a : tiles) std::cout << a.printTile() << std::endl;
}