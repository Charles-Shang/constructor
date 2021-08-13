#include "game.h"
#include <stdio.h>
#include <fstream>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

Game::Game(std::default_random_engine _rng) : seed{_rng} {}

// void loadFromBoard(Board &thisBoard, std::string fileName) {}

// void loadFromLoad(Board &thisBoard, std::string fileName) {}

// void loadFromRandom(Board &thisBoard) {}

void Game::initializeGame(int inputMode, std::string fileName) {
    /*
     * 1. -load
     * 2. -board
     * 3. -random-board
     * 4. layout.txt
     */

    switch (inputMode) {
        default:
            thisBoard.init(4);
            break;
    }
}

void Game::beginGame() {
    int location;

    for (auto player : allPlayers) {
        cout << "Builder " << player->getBuilderName()
             << ", where do you want to build a basement?" << endl;
        while (true) {
            cin >> location;
            if (thisBoard.checkCanBuildResAt(location)) {
                thisBoard.buildResAt(location, curPlayer);
                player->buildResidence(location, true);
                cout << player->getBuilderName() << " has built: ";
                cout << "a basement at " << location << endl;
                break;
            } else {
                cout << "You cannot build here. Try again!" << endl;
            }
        }
    }

    for (int i = 3; i >= 0; --i) {
        cout << "Builder " << allPlayers[i]->getBuilderName()
             << ", where do you want to build a basement?" << endl;
        while (true) {
            cin >> location;
            if (thisBoard.checkCanBuildResAt(location)) {
                thisBoard.buildResAt(location, curPlayer);
                allPlayers[i]->buildResidence(location, true);
                cout << allPlayers[i]->getBuilderName() << " has built: ";
                cout << "a basement at " << location << endl;
                break;
            } else {
                cout << "You cannot build here. Try again!" << endl;
            }
        }
    }
}

void Game::play() {
    std::shared_ptr<Builder> Blue = std::make_shared<Builder>(0, seed);
    std::shared_ptr<Builder> Red = std::make_shared<Builder>(1, seed);
    std::shared_ptr<Builder> Orange = std::make_shared<Builder>(2, seed);
    std::shared_ptr<Builder> Yellow = std::make_shared<Builder>(3, seed);
    allPlayers = {Blue, Red, Orange, Yellow};
    curPlayer = 0;  // reprents by color index
    // now start the game
    beginGame();
    displayBoard();
    while (true) {
        beginTurn();
        duringTheTurn();

        if (allPlayers[curTurn].calculatePoints() == 10) {
            // not in the guideline
            cout << "Congratulations! You win!" << endl;
            cout << "Would you like to play again?" << endl;
            std::string newGame;
            cin >> newGame;
            if (newGame == "yes") {
                // need to initialize the board and builders
                play();
            } else if (newGame == "no") {
                break;  // end the game (do we need to destroy anything?)
            }
        }

        if (curTurn == 4)
            curTurn = 0;
        else
            ++curTurn;
    }
}

void Game::newMain() {
    char cmd;
    while (true) {
        cin >> cmd;
        return;
        // if (cmd == 'a') {
        //     // printBoard();
        // } else if (cmd == 'b') {
        //     thisBoard.displayTile();
        // } else if (cmd == 'c') {
        //     thisBoard.displayConnections();
        // } else if (cmd == 'd') {
        //     for (int i = 0; i < 53; i++)
        //         cout << thisBoard.vertexToTile(i) << " ";
        //     cout << endl;

        //     for (int i = 0; i < 72; i++) cout << thisBoard.edgeToTile(i) << "
        //     "; cout << endl;
        // } else if (cmd == 'e') {
        //     Builder Blue(0, seed), Red(1, seed), Orange(2, seed),
        //         Yellow(3, seed);
        //     allPlayers = {Blue, Red, Orange, Yellow};
        //     for (size_t i = 0; i < allPlayers.size(); i++) {
        //         cout << allPlayers[i].getColourName() << endl;
        //     }
        // } else if (cmd == 'q') {
        //     return;
        // }
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
void Game::displayBoard() {
    std::ifstream boardFile;

    try {
        boardFile = std::ifstream{"boardTemplate.txt"};
    } catch (const std::exception &e) {
        std::cerr << "Opening file boardTemplate.txt failed." << std::endl;
    }

    int typeCount = 0, valueCount = 0, geeseCount = 0;
    int vertixCount = 0, edgeCount = 0;
    char c;

    while (true) {
        boardFile >> c;
        if (boardFile.eof()) break;

        if (c == 'T') {  // T for Type
            boardFile >> c >> c >> c >> c >> c;
            printTileType(thisBoard.getTileTypeAtLocation(typeCount++));
        } else if (c == 'V') {  // V for Value
            boardFile >> c;
            printTileValue(thisBoard.getTileValueAtLocation(valueCount++));
        } else if (c == 'G') {  // G for Geese
            boardFile >> c >> c >> c >> c >> c;
            if (!thisBoard.getTileHasGeeseAtLocation(geeseCount++)) {
                std::cout << "      ";
            } else {
                std::cout << "GEESE ";
            }
        } else if (c == ',') {  // , for new line
            std::cout << std::endl;
        } else if (c == '_') {  // _ for space
            std::cout << " ";
        } else if (c == 'X') {
            boardFile >> c;
            cout << builtInWhichColour(vertixCount++, "residence");
        } else if (c == 'Y') {
            boardFile >> c;
            cout << builtInWhichColour(edgeCount++, "road");
        } else {
            std::cout << c;
        }
    }
}

std::string Game::builtInWhichColour(int location, std::string type) {
    std::string temp = "";
    if (location <= 9) temp += " ";
    temp += std::to_string(location);

    for (auto player : allPlayers) {
        std::string newTemp;
        if (type == "residence")
            newTemp = player->getResDisplay(location, "residence");
        else
            newTemp = player->getResDisplay(location, "road");

        if (newTemp != temp) return newTemp;
    }

    return temp;
}