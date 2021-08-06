#include "game.h"
#include <stdio.h>
#include <fstream>
#include <iostream>

void loadFromLayout(Board &thisBoard, std::string fileName) {
    std::ifstream layoutFile;

    try {
        layoutFile = std::ifstream{fileName};
    } catch (const std::exception& e) {
        std::cerr << "Opening file layout.txt failed." << std::endl;
    }

    int resources[19], tileValues[19], num;

    for (int i = 0; i < 19; i++) {
        layoutFile >> num;
        if (layoutFile.eof()) break;
        resources[i] = num;
        layoutFile >> num;
        tileValues[i] = num;
    }

    thisBoard.initBoard(resources, tileValues);
}

void Game::initializeGame(int inputReadMode, std::string fileName) {
    /*
     * 1. -random-board
     * 2. -load
     * 3. -board
     * 4. layout.txt
     */

    switch (inputReadMode) {
        default:
            loadFromLayout(thisBoard, fileName);
            break;
    }
}

void Game::play() { thisBoard.printBoard(); }