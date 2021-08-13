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

void Game::beginTurn() {
    printBoard();
    cout << "Builder " << allPlayers[curPlayer]->getBuilderName() << "'s turn."
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
            allPlayers[curPlayer]->switchFairDice(false);
        } else if (cmd == "fair") {
            allPlayers[curPlayer]->switchFairDice(true);
        } else if (cmd == "roll") {
            int diceResult = allPlayers[curPlayer]->rollDice();
            if (diceResult == 7) {
                moveGeese();
            } else {
                gainResources(diceResult);
            }
        } else {
            cout << "Invalid Command!";
            cout << "Try again with \"load\", \"fair\" or \"roll\"" << endl;
        }
    }
}

bool Game::play() {
    std::shared_ptr<Builder> Blue = std::make_shared<Builder>(0, seed);
    std::shared_ptr<Builder> Red = std::make_shared<Builder>(1, seed);
    std::shared_ptr<Builder> Orange = std::make_shared<Builder>(2, seed);
    std::shared_ptr<Builder> Yellow = std::make_shared<Builder>(3, seed);
    allPlayers = {Blue, Red, Orange, Yellow};
    curPlayer = 0;  // reprents by color index
    // now start the game
    std::cout << "----- Game setup -----" << std::endl;
    beginGame();
    printBoard();
    std::cout << "----- Game starts -----" << std::endl;
    while (true) {
        beginTurn();
        duringTheTurn();

        if (allPlayers[curPlayer]->calculatePoints() == 10) {
            // not in the guideline
            cout << "Congratulations! You win!" << endl;
            cout << "Would you like to play again?" << endl;
            std::string newGame;
            cin >> newGame;
            if (newGame == "yes") {
                return true;
            } else if (newGame == "no") {
                return false;  // end the game (do we need to destroy anything?)
            }
        }

        curPlayer = curPlayer == 4 ? 0 : curPlayer + 1;
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
void Game::printBoard() {
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

std::string getRssType(int type) {
    switch (type) {
        case 0:
            return "BRICK";
        case 1:
            return "ENERGY";
        case 2:
            return "GLASS";
        case 3:
            return "HEAT";
        case 4:
            return "WIFI";
        default:
            return "PARK";
    }
}

int getColourIndex(std::string colour) {
    if (colour == "BLUE")
        return 0;
    else if (colour == "RED")
        return 1;
    else if (colour == "ORANGE")
        return 2;
    else if (colour == "YELLOW")
        return 3;

    return 99999;  // this should never be reached
}

void Game::moveGeese() {
    // everyone randomly lose resources
    for (auto curPlayer : allPlayers) {
        int totalRss = curPlayer->calculateResouceSum();
        if (totalRss >= 10) {
            int lose = totalRss / 2;
            cout << "Builder " << curPlayer->getBuilderName() << " loses "
                 << lose << " resources to the geese. They lose:" << endl;

            std::vector<int> lostList = {0, 0, 0, 0, 0};
            std::vector<int> rssLst = curPlayer->listAllRss();
            for (int i = 0; i < lose; ++i) {
                std::shuffle(rssLst.begin(), rssLst.end(), seed);
                int indexType = rssLst[0];
                curPlayer->modifiesResources(indexType, -1);
                lostList[indexType]++;
                rssLst.erase(rssLst.begin());
            }

            for (int i = 0; i < 5; i++)
                cout << lostList[i] << " " << getRssType(i) << endl;
        }
    }
    // move Geese
    cout << "Choose where to place the GEESE." << endl;

    int desitation, current = thisBoard.whichHasGeese();
    while (true) {
        try {
            std::cin >> desitation;
        } catch (const std::exception &e) {
            cout << "Invalid Number. Try again with 0-18!" << endl;
            continue;
        }

        if (!(0 <= desitation && desitation <= 18)) {
            cout << "Invalid Number. Try again with 0-18!" << endl;
            continue;
        } else if (desitation == current) {
            cout << "Cannot choose the current (" << current << ")" << endl;
            continue;
        }

        break;
    }

    thisBoard.transferGeese(current, desitation);
    cout << "Now Geese is at tile " << desitation << "." << endl;

    std::vector<int> stolenLst = thisBoard.getPlayersOnTile(desitation);
    for (size_t i = 0; i < stolenLst.size(); i++)
        if (stolenLst[i] == curPlayer) stolenLst.erase(stolenLst.begin() + i);

    if (stolenLst.empty()) {
        cout << "Builder " << allPlayers[curPlayer]->getBuilderName()
             << " has no builders to steal from." << std::endl;
    } else {
        cout << "Builder " << allPlayers[curPlayer]->getBuilderName()
             << " can choose to steal from ";
        for (size_t i = 0; i < stolenLst.size() - 1; i++)
            cout << allPlayers[stolenLst[i]]->getBuilderName() << ", ";

        cout << allPlayers[stolenLst.back()]->getBuilderName() << ".";

        cout << "Choose a builder to steal from." << endl;

        std::string chosenToSteal;
        while (true) {
            try {
                std::cin >> chosenToSteal;
            } catch (const std::exception &e) {
                cout << "Invalid Input. Try again!" << endl;
                continue;
            }

            if (std::count(stolenLst.begin(), stolenLst.end(),
                           getColourIndex(chosenToSteal)))
                break;
            else
                cout << "Input is not found in provided lst. Try again!"
                     << endl;
        }

        int stolenIndex = getColourIndex(chosenToSteal);
        std::vector<int> listofRss = allPlayers[stolenIndex]->listAllRss();
        std::shuffle(listofRss.begin(), listofRss.end(), seed);
        int indexType = listofRss[0];
        allPlayers[stolenIndex]->modifiesResources(indexType, -1);
        allPlayers[curPlayer]->modifiesResources(indexType, 1);

        cout << "Builder " << allPlayers[curPlayer]->getBuilderName()
             << "steals " << getRssType(indexType) << " from builder "
             << chosenToSteal << "." << endl;
    }
}

void Game::gainResources(int diceResult) {
    // ****
}