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

void printBuilderColour(int colour) {
    if (colour == 0) {
        std::cout << "Blue";
    } else if (colour == 1) {
        std::cout << "Red";
    } else if (colour == 2) {
        std::cout << "Orange";
    } else {
        std::cout << "Yellow";
    }
}

void Game::beginTurn(Builder curPlayer) {
    thisBoard.printBoard();

    std::cout << "Builder ";
    printBuilderColour(curPlayer.getColour());
    std::cout << "'s turn." << std::endl;

    std::string cmd;

    if (cmd == "load") {
    } else if (cmd == "fair") {
    } else if (cmd == "roll") {
        curPlayer.rollDice();  // what happens after rolled dice?
    }
}
void Game::duringTheTurn(Builder curPlayer, std::vector<Builder> allPlayers) {
    std::string cmd;
    while (1) {
        try {
            std::cin >> cmd;
        } catch (std::ios::failure&) {
            if (std::cin.eof()) break;
            std::cin.clear();
            std::cin.ignore();
        }
        if (cmd == "board") {
            thisBoard.printBoard();
        } else if (cmd == "status") {
            for (int i = 0; i < 4; ++i) {
                allPlayers[i].printStatus();
            }
        } else if (cmd == "residences") {
            curPlayer.printResidence();
        } else if (cmd == "build-road") {
            int roadNum = 0;
            std::cin >> roadNum;
            if (!curPlayer.canBuildRoad()) {
                std::cout << "You do not have enough resources" << std::endl;
            } else if (thisBoard.buildRoad(roadNum, curPlayer.getColour())) {
                curPlayer.buildRoad(roadNum);
                printBuilderColour(curPlayer.getColour());
                std::cout << " has built: a road at" << roadNum << std::endl;
            } else {
                std::cout << "You cannot build here." << std::endl;
            }
        } else if (cmd == "build-res") {
            int housingNum = 0;
            std::cin >> housingNum;
            if (!curPlayer.canBuildResidence()) {
                std::cout << "You do not have enough resources";
            } else if (thisBoard.buildResidence(housingNum,
                                                curPlayer.getColour())) {
                curPlayer.buildResidence(housingNum);
                printBuilderColour(curPlayer.getColour());
                std::cout << " has built: a basement at" << housingNum
                          << std::endl;
            } else {
                std::cout << "You cannot build here." << std::endl;
            }
        } else if (cmd == "improve") {
            int housingNum = 0;
            std::cin >> housingNum;
            if (!curPlayer.haveResidence(housingNum)) {
                std::cout << "You do not have a residence at " << housingNum
                          << std::endl;
            } else if (!curPlayer.canUpgrade(housingNum)) {
                std::cout << "You do not have enough resources" << std::endl;
            } else if (curPlayer.highestLevel(housingNum)) {
                std::cout << "Your residence is already at the highest level"
                          << std::endl;
            } else {
                int idx = curPlayer.upgradeResidence(housingNum);
                printBuilderColour(curPlayer.getColour());
                std::cout << " has a level ";
                curPlayer.printRecentUpgrade(idx);
                std::cout << "residence at " << housingNum << std::endl;
            }
        } else if (cmd == "trade") {
            int colour;
            int give;
            int take;
            std::cin >> colour >> give >> take;
            // how do we trade?
        } else if (cmd == "next") {
            break;
        } else if (cmd == "save") {
            std::string saveFile;
            std::cin >> saveFile;
            // how do we save?
        } else if (cmd == "help") {
            printHelp();
        } else {
            std::cout << "Invalid command" << std::endl;
        }
    }
}

void Game::play() {
    std::vector<Builder> allPlayers;
    Builder Blue, Red, Orange, Yellow;
    allPlayers.emplace_back(Blue);
    allPlayers.emplace_back(Red);
    allPlayers.emplace_back(Orange);
    allPlayers.emplace_back(Yellow);
    int curPlayer = 0;  // need to change to the number of
                        // the first player by a rolled dice
    // now start the game
    while (1) {
        beginTurn(allPlayers[curPlayer]);
        duringTheTurn(allPlayers[curPlayer], allPlayers);

        if (allPlayers[curPlayer].calculatePoints() == 10) {
            std::cout << "Congratulations! You win!"
                      << std::endl;  // not in the guideline
            std::cout << "Would you like to play again?" << std::endl;
            std::string newGame;
            std::cin >> newGame;
            if (newGame == "yes") {
                // need to initialize the board and builders
                play();
            } else if (newGame == "no") {
                break;  // end the game (do we need to destroy anything?)
            }
        }
        if (curPlayer == 4) {
            curPlayer = 0;
        } else {
            ++curPlayer;
        }
    }
}

void Game::newMain() {
    char cmd;
    while (true) {
        std::cin >> cmd;
        if (cmd == 'b') {
            thisBoard.printBoard();
        } else if (cmd == 't') {
            thisBoard.displayTile();
        } else if (cmd == 'c') {
            thisBoard.displayConnections();
        } else if (cmd == 'm') {
            for (int i = 0; i < 53; i++)
                std::cout << thisBoard.vertexToTile(i) << " ";

            std::cout << std::endl;

            for (int i = 0; i < 72; i++)
                std::cout << thisBoard.edgeToTile(i) << " ";

            std::cout << std::endl;
        }
    }
}