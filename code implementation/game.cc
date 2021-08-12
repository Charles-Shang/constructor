#include "game.h"
#include <stdio.h>
#include <fstream>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void loadFromLayout(Board &thisBoard, std::string fileName) {
    std::ifstream layoutFile;

    try {
        layoutFile = std::ifstream{fileName};
    } catch (const std::exception &e) {
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

    thisBoard.defaultInitBoard(resources, tileValues);
}

// void loadFromBoard(Board &thisBoard, std::string fileName) {}

// void loadFromLoad(Board &thisBoard, std::string fileName) {}

// void loadFromRandom(Board &thisBoard) {}

void Game::initializeGame(int inputMode, std::string fileName, unsigned _seed) {
    /*
     * 1. -load
     * 2. -board
     * 3. -random-board
     * 4. layout.txt
     */

    seed = _seed;

    switch (inputMode) {
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

void Game::beginTurn() {
    thisBoard.printBoard();
    cout << "Builder " << allPlayers[curTurn].getColourName() << "'s turn."
         << endl;

    std::string cmd;
    while (true) {
        try {
            cin >> cmd;
        } catch (std::ios::failure &) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore();
        }

        if (cmd == "load") {
            allPlayers[curTurn].switchFairDice(false);
        } else if (cmd == "fair") {
            allPlayers[curTurn].switchFairDice(true);
        } else if (cmd == "roll") {
            int diceResult =
                allPlayers[curTurn]
                    .rollDice();  // what happens after rolled dice?
        } else {
            cout << "Invalid Command!";
            cout << "Try again with \"load\", \"fair\" or \"roll\"" << endl;
        }
    }
}

void Game::duringTheTurn() {
    std::string cmd;
    while (true) {
        try {
            cin >> cmd;
        } catch (std::ios::failure &) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore();
        }

        if (cmd == "board") {
            thisBoard.printBoard();
        } else if (cmd == "status") {
            for (int i = 0; i < 4; ++i) allPlayers[i].printStatus();
        } else if (cmd == "residences") {
            allPlayers[curTurn].printResidence();
        } else if (cmd == "build-road") {
            int roadNum = 0;
            cin >> roadNum;
            if (!allPlayers[curTurn].canBuildRoad()) {
                cout << "You do not have enough resources." << endl;
            } else if (thisBoard.buildRoad(roadNum,
                                           allPlayers[curTurn].getColour())) {
                allPlayers[curTurn].buildRoad(roadNum);
                cout << allPlayers[curTurn].getColourName();
                cout << " has built: a road at " << roadNum << endl;
            } else {
                cout << "You cannot build here." << endl;
            }
        } else if (cmd == "build-res") {
            int location = 0;
            cin >> location;
            if (!allPlayers[curTurn].canBuildResidence()) {
                cout << "You do not have enough resources.";
            } else if (thisBoard.buildRes(location,
                                          allPlayers[curTurn].getColour())) {
                allPlayers[curTurn].buildResidence(location, false);
                cout << allPlayers[curTurn].getColourName();
                cout << " has built: a basement at " << location << endl;
            } else {
                cout << "You cannot build here." << endl;
            }
        } else if (cmd == "improve") {
            int location = 0;
            cin >> location;
            if (!allPlayers[curTurn].haveResidence(location)) {
                cout << "You do not have a residence at " << location << endl;
            } else if (!allPlayers[curTurn].canUpgrade(location)) {
                cout << "You do not have enough resources." << endl;
            } else if (allPlayers[curTurn].highestLevel(location)) {
                cout << "The residence is at the highest level." << endl;
            } else {
                cout << "The residence at " << location << " is now a ";
                cout << allPlayers[curTurn].upgradeResidence(location) << endl;
            }
        } else if (cmd == "trade") {
            int colour;
            int give;
            int take;
            cin >> colour >> give >> take;
            cout << allPlayers[curTurn].getColourName() << " offers "
                 << allPlayers[colour].getColourName() << " one "
                 << getResourceName(give) << " for one "
                 << getResourceName(take) << "." << endl;
            cout << "Does " << allPlayers[colour].getColourName()
                 << " accept this offer?" << endl;
            std::string answer;
            cin >> answer;
            if (answer == "yes") {
                allPlayers[curTurn].trade(give, take);
                allPlayers[colour].trade(take, give);
                cout << "Builder " << allPlayers[curTurn].getColourName()
                     << " gained: ";
                cout << "1 " << getResourceName(take) << ", lose 1 "
                     << getResourceName(give) << endl;
                cout << "Builder " << allPlayers[colour].getColourName()
                     << " gained: ";
                cout << "1 " << getResourceName(give) << ", lose 1 "
                     << getResourceName(take) << endl;
            } else {
                cout << "No builders gained resources." << endl;
            }
        } else if (cmd == "next") {
            break;
        } else if (cmd == "save") {
            saveGame();
        } else if (cmd == "help") {
            printHelp();
        } else {
            cout << "Invalid command" << endl;
        }
    }
}

void Game::saveGame() {
    std::string saveFile;
    while (true) {
        cin >> saveFile;

        std::ofstream file(saveFile);
        if (file.is_open()) {
            file << curTurn << std::endl;
            for (size_t i = 0; i < allPlayers.size(); i++)
                file << allPlayers[i].getData() << std::endl;

            file << thisBoard.getBoardData() << std::endl;
            file << thisBoard.whichHasGeese();

        } else {
            std::cout << "Unable to save file to " << saveFile << std::endl;
            std::cout << "Try another file." << saveFile << std::endl;
        }
    }
}

std::string getResourceName(int resource) {
    if (resource == 0) {
        return "BRICK";
    } else if (resource == 1) {
        return "ENERGY";
    } else if (resource == 2) {
        return "GLASS";
    } else if (resource == 3) {
        return "HEAT";
    } else {
        return "WIFI";
    }
}

void Game::beginGame() {
    int location;
    for (int i = 0; i < 4; ++i) {
        cout << "Builder" << allPlayers[i].getColourName()
             << ", where do you want to build a basement?" << endl;
        cin >> location;
        if (thisBoard.buildRes(location, allPlayers[i].getColour())) {
            allPlayers[i].buildResidence(location, true);
            cout << allPlayers[i].getColourName();
            cout << " has built: a basement at " << location << endl;
        } else {
            cout << "You cannot build here." << endl;
        }
    }
    for (int i = 3; i >= 0; --i) {
        cout << "Builder" << allPlayers[i].getColourName()
             << ", where do you want to build a basement?" << endl;
        cin >> location;
        if (thisBoard.buildRes(location, allPlayers[i].getColour())) {
            allPlayers[i].buildResidence(location, true);
            cout << allPlayers[i].getColourName();
            cout << " has built: a basement at " << location << endl;
        } else {
            cout << "You cannot build here." << endl;
        }
    }
}

void Game::play() {
    Builder Blue(seed), Red(seed), Orange(seed), Yellow(seed);
    allPlayers = {Blue, Red, Orange, Yellow};
    curTurn = 0;  // reprents by color index
    // now start the game
    beginGame();
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