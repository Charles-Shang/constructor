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

void Game::initializeGame(int inputMode, std::string fileName,
                          std::default_random_engine _rng) {
    /*
     * 1. -load
     * 2. -board
     * 3. -random-board
     * 4. layout.txt
     */

    seed = _rng;

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
        int totalRss = curPlayer.calculateResouceSum();
        if (totalRss >= 10) {
            int lose = totalRss / 2;
            cout << "Builder " << curPlayer.getColourName() << " loses " << lose
                 << " resources to the geese. They lose:" << endl;

            std::vector<int> lostList = {0, 0, 0, 0, 0};
            std::vector<int> rssLst = curPlayer.listAllRss();
            for (int i = 0; i < lose; ++i) {
                std::shuffle(rssLst.begin(), rssLst.end(), seed);
                int indexType = rssLst[0];
                curPlayer.modifiesResources(indexType, -1);
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
    for (size_t i = 0; i < stolenLst.size(); i++) {
        if (stolenLst[i] == curTurn) {
            stolenLst.erase(stolenLst.begin() + i);
        }
    }

    if (stolenLst.empty()) {
        cout << "Builder " << allPlayers[curTurn].getColourName()
             << " has no builders to steal from." << std::endl;
    } else {
        cout << "Builder " << allPlayers[curTurn].getColourName()
             << " can choose to steal from ";
        for (size_t i = 0; i < stolenLst.size() - 1; i++)
            cout << allPlayers[stolenLst[i]].getColourName() << ", ";

        cout << allPlayers[stolenLst.back()].getColourName() << ".";

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
        std::vector<int> listofRss = allPlayers[stolenIndex].listAllRss();
        std::shuffle(listofRss.begin(), listofRss.end(), seed);
        int indexType = listofRss[0];
        allPlayers[stolenIndex].modifiesResources(indexType, -1);
        allPlayers[curTurn].modifiesResources(indexType, 1);

        cout << "Builder " << allPlayers[curTurn].getColourName() << "steals "
             << getRssType(indexType) << " from builder " << chosenToSteal
             << "." << endl;
    }
}

void Game::gainResources(int diceResult) {
    std::vector<int> tileNumLst = thisBoard.tileValToNum(diceResult);
    for (int curTile : tileNumLst) {
        int rss = thisBoard.getRssOnTile(curTile);
        std::vector<int> playerLst = thisBoard.getPlayersOnTile(curTile);
        std::vector<int> locationLst = thisBoard.getResLocOnTile(curTile);
        int idx = 0;
        for (int player : playerLst) {
            int level =
                allPlayers[player].getResLevelOnVertex(locationLst[idx]);
            allPlayers[player].modifiesResources(rss, level);
            ++idx;
        }
    }
}

void Game::beginTurn() {
    printBoard();
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
            printBoard();
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
                 << getRssType(give) << " for one " << getRssType(take) << "."
                 << endl;
            cout << "Does " << allPlayers[colour].getColourName()
                 << " accept this offer?" << endl;
            std::string answer;
            cin >> answer;
            if (answer == "yes") {
                if (allPlayers[curTurn].getRss(give) >= 1 &&
                    allPlayers[colour].getRss(take) >= 1) {
                    allPlayers[curTurn].trade(give, take);
                    allPlayers[colour].trade(take, give);
                    cout << "Builder " << allPlayers[curTurn].getColourName()
                         << " gained: ";
                    cout << "1 " << getRssType(take) << ", lose 1 "
                         << getRssType(give) << endl;
                    cout << "Builder " << allPlayers[colour].getColourName()
                         << " gained: ";
                    cout << "1 " << getRssType(give) << ", lose 1 "
                         << getRssType(take) << endl;
                } else {
                    cout << "You do not have enough resources to trade."
                         << endl;
                }
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
            printBoard();
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
            cout << resBuiltInWhichColour(vertixCount++);
        } else if (c == 'Y') {
            boardFile >> c;
            cout << roadBuiltInWhichColour(edgeCount++);
        } else {
            std::cout << c;
        }
    }
}

std::string Game::resBuiltInWhichColour(int location) {
    std::string temp = "";
    if (location <= 9) temp += " ";
    temp += std::to_string(location);

    for (size_t i = 0; i < allPlayers.size(); i++) {
        std::string newTemp = allPlayers[i].getResDisplayOnBoard(location);
        if (newTemp != temp) return newTemp;
    }

    return temp;
}

std::string Game::roadBuiltInWhichColour(int location) {
    std::string temp = "";
    if (location <= 9) temp += " ";
    temp += std::to_string(location);

    for (size_t i = 0; i < allPlayers.size(); i++) {
        std::string newTemp = allPlayers[i].getRoadDisplayOnBoard(location);
        if (newTemp != temp) return newTemp;
    }

    return temp;
}