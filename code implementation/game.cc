#include "game.h"
#include <stdio.h>
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

void loadFromLayout(Board& thisBoard, std::string fileName) {
    std::ifstream layoutFile;

    try {
        layoutFile = std::ifstream{fileName};
    } catch (const std::exception& e) {
        std::cerr << "Opening file layout.txt failed." << endl;
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
    cout << "Valid commands:" << endl;
    cout << "board" << endl;
    cout << "status" << endl;
    cout << "residences" << endl;
    cout << "build-road <edge#>" << endl;
    cout << "build-res <housing#>" << endl;
    cout << "improve <housing#>" << endl;
    cout << "trade <colour> <give> <take>" << endl;
    cout << "next" << endl;
    cout << "save <file>" << endl;
    cout << "help" << endl;
}

void Game::beginTurn(Builder curPlayer) {
    thisBoard.printBoard();
    cout << "Builder " << curPlayer.getColourName() << "'s turn." << endl;

    std::string cmd;
    while (true) {
        try {
            std::cin >> cmd;
        } catch (std::ios::failure&) {
            if (std::cin.eof()) break;
            std::cin.clear();
            std::cin.ignore();
        }

        if (cmd == "load") {
            break;
        } else if (cmd == "fair") {
            break;
        } else if (cmd == "roll") {
            curPlayer.rollDice();  // what happens after rolled dice?
            break;
        } else {
            cout << "Invalid Command!";
            cout << "Try again with \"load\", \"fair\" or \"roll\"" << endl;
        }
    }
}
void Game::duringTheTurn(Builder curPlayer, std::vector<Builder> allPlayers) {
    std::string cmd;
    while (true) {
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
            for (int i = 0; i < 4; ++i) allPlayers[i].printStatus();
        } else if (cmd == "residences") {
            curPlayer.printResidence();
        } else if (cmd == "build-road") {
            int roadNum = 0;
            std::cin >> roadNum;
            if (!curPlayer.canBuildRoad()) {
                cout << "You do not have enough resources." << endl;
            } else if (thisBoard.buildRoad(roadNum, curPlayer.getColour())) {
                curPlayer.buildRoad(roadNum);
                cout << curPlayer.getColourName();
                cout << " has built: a road at " << roadNum << endl;
            } else {
                cout << "You cannot build here." << endl;
            }
        } else if (cmd == "build-res") {
            int location = 0;
            std::cin >> location;
            if (!curPlayer.canBuildResidence()) {
                cout << "You do not have enough resources.";
            } else if (thisBoard.buildRes(location, curPlayer.getColour())) {
                curPlayer.buildResidence(location);
                cout << curPlayer.getColourName();
                cout << " has built: a basement at " << location << endl;
            } else {
                cout << "You cannot build here." << endl;
            }
        } else if (cmd == "improve") {
            int location = 0;
            std::cin >> location;
            if (!curPlayer.haveResidence(location)) {
                cout << "You do not have a residence at " << location << endl;
            } else if (!curPlayer.canUpgrade(location)) {
                cout << "You do not have enough resources." << endl;
            } else if (curPlayer.highestLevel(location)) {
                cout << "The residence is at the highest level." << endl;
            } else {
                cout << "The residence at " << location << " is now a ";
                cout << curPlayer.upgradeResidence(location) << endl;
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
            cout << "Invalid command" << endl;
        }
    }
}

void Game::play() {
    Builder Blue, Red, Orange, Yellow;
    std::vector<Builder> allPlayers = {Blue, Red, Orange, Yellow};
    int curPlayer = 0;  // reprents by color index
    // now start the game
    while (true) {
        beginTurn(allPlayers[curPlayer]);
        duringTheTurn(allPlayers[curPlayer], allPlayers);

        if (allPlayers[curPlayer].calculatePoints() == 10) {
            // not in the guideline
            cout << "Congratulations! You win!" << endl;
            cout << "Would you like to play again?" << endl;
            std::string newGame;
            std::cin >> newGame;
            if (newGame == "yes") {
                // need to initialize the board and builders
                play();
            } else if (newGame == "no") {
                break;  // end the game (do we need to destroy anything?)
            }
        }
        if (curPlayer == 4)
            curPlayer = 0;
        else
            ++curPlayer;
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
                cout << thisBoard.vertexToTile(i) << " ";
            cout << endl;

            for (int i = 0; i < 72; i++) cout << thisBoard.edgeToTile(i) << " ";
            cout << endl;
        }
    }
}