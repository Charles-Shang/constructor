#include "game.h"
#include <stdio.h>
#include <fstream>
#include <iostream>

void loadFromLayout(Board& thisBoard, std::string fileName) {
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

void Game::printHelp() {
    std::cout << "Valid commands:" << std::endl;
    std::cout << "board" << std::endl;
    std::cout << "status" << std::endl;
    std::cout << "residences" << std::endl;
    std::cout << "build-road <edge#>" << std::endl;
    std::cout << "build-res <housing#>" << std::endl;
    std::cout << "improve <housing#>" << std::endl;
    std::cout << "trade <colour> <give> <take>" << std::endl;
    std::cout << "next" << std::endl;
    std::cout << "save <file>" << std::endl;
    std::cout << "help" << std::endl;
}

void Game::play() { 
    thisBoard.printBoard(); 

    std::string cmd;
    while (1) {
        try {
            std::cin >> cmd;
        } catch (std::ios::failure &) {
            if (std::cin.eof())
                break;
            std::cin.clear();
            std::cin.ignore();
        }

        if (cmd == "board") {
            
        } else if (cmd == "status") {  
        
        } else if (cmd == "residences") {

        } else if (cmd == "build-road") {
            int roadNum = 0;
            std::cin >> roadNum;

        } else if (cmd == "build-res") {
            int housingNum = 0;
            std::cin >> housingNum;

        } else if (cmd == "improve") {
            int housingNum = 0;
            std::cin >> housingNum;

        } else if (cmd == "trade") {
            int colour;
            int give;
            int take;
            std::cin >> colour >> give >> take;

        } else if (cmd == "next") {

        } else if (cmd == "save") {
            std::string saveFile;
            std::cin >> saveFile;

        } else if (cmd == "help") {
            printHelp();
        }
    }
}