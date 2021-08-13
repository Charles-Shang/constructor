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

    allPlayers[curPlayer]->printStatus();

    std::string cmd;

    std::cout << "Choose your dice and roll!" << std::endl;
    std::cout << "Commands: \"load\", \"fair\" and \"roll\"." << std::endl;
    while (true) {
        try {
            cin >> cmd;
        } catch (std::ios::failure &e) {
            if (cin.eof()) break;
            cin.clear();
            cin.ignore();
        }

        if (cmd == "load") {
            std::cout << "Now you have loaded dice!" << std::endl;
            allPlayers[curPlayer]->switchFairDice(false);
        } else if (cmd == "fair") {
            std::cout << "Now you have fair dice!" << std::endl;
            allPlayers[curPlayer]->switchFairDice(true);
        } else if (cmd == "roll") {
            int diceResult = allPlayers[curPlayer]->rollDice();
            std::cout << "Rolled dice is " << diceResult << " !" << std::endl;
            if (diceResult == 7) {
                moveGeese();
            } else {
                gainResources(diceResult);
            }

            break;
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
            for (int i = 0; i < 4; ++i) allPlayers[i]->printStatus();
        } else if (cmd == "residences") {
            allPlayers[curPlayer]->printResidence();
        } else if (cmd == "build-road") {
            int roadNum = 0;
            cin >> roadNum;
            if (!thisBoard.checkCanBuildRoadAt(curPlayer, roadNum)) {
                cout << "You cannot build here." << endl;
            } else if (!allPlayers[curPlayer]->haveEnoughRssForRoad()) {
                cout << "You do not have enough resources." << endl;
            } else {
                allPlayers[curPlayer]->buildRoad(roadNum);
                thisBoard.buildRoadAt(curPlayer, roadNum);
                cout << allPlayers[curPlayer]->getBuilderName();
                cout << " has built: a road at " << roadNum << endl;
            }
        } else if (cmd == "build-res") {
            int location = 0;
            cin >> location;
            if (!allPlayers[curPlayer]->haveEnoughRssForResidence()) {
                cout << "You do not have enough resources.";
            } else if (thisBoard.checkCanBuildResAt(location)) {
                thisBoard.buildResAt(location, curPlayer);
                allPlayers[curPlayer]->buildResidence(location);
                cout << allPlayers[curPlayer]->getBuilderName();
                cout << " has built: a basement at " << location << endl;
            } else {
                cout << "You cannot build here." << endl;
            }
        } else if (cmd == "improve") {
            int location = 0;
            cin >> location;
            if (!allPlayers[curPlayer]->haveResidence(location)) {
                cout << "You do not have a residence at " << location << endl;
            } else if (allPlayers[curPlayer]->highestLevel(location)) {
                cout << "The residence is at the highest level." << endl;
            } else if (!allPlayers[curPlayer]->haveRssForImprove(location)) {
                cout << "You do not have enough resources." << endl;
            } else {
                cout << "The residence at " << location << " is now a ";
                cout << allPlayers[curPlayer]->upgradeResidence(location)
                     << endl;
            }
        } else if (cmd == "trade") {
            int colour;
            int give;
            int take;
            cin >> colour >> give >> take;
            cout << allPlayers[curPlayer]->getBuilderName() << " offers "
                 << allPlayers[colour]->getBuilderName() << " one "
                 << getRssType(give) << " for one " << getRssType(take) << "."
                 << endl;
            cout << "Does " << allPlayers[colour]->getBuilderName()
                 << " accept this offer?" << endl;
            std::string answer;
            cin >> answer;
            if (answer == "yes") {
                if (allPlayers[curPlayer]->getNumOfRssOf(give) >= 1 &&
                    allPlayers[colour]->getNumOfRssOf(give) >= 1) {
                    allPlayers[curPlayer]->trade(give, take);
                    allPlayers[colour]->trade(take, give);
                    cout << "Builder "
                         << allPlayers[curPlayer]->getBuilderName()
                         << " gained: ";
                    cout << "1 " << getRssType(take) << ", lose 1 "
                         << getRssType(give) << endl;
                    cout << "Builder " << allPlayers[colour]->getBuilderName()
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

bool Game::play() {
    std::shared_ptr<Builder> Blue = std::make_shared<Builder>(0, seed);
    std::shared_ptr<Builder> Red = std::make_shared<Builder>(1, seed);
    std::shared_ptr<Builder> Orange = std::make_shared<Builder>(2, seed);
    std::shared_ptr<Builder> Yellow = std::make_shared<Builder>(3, seed);
    allPlayers = {Blue, Red, Orange, Yellow};
    curPlayer = 0;  // reprents by color index
    // now start the game
    std::cout << "----- Game setup -----" << std::endl;
    printBoard();
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
    std::vector<int> tileNumLst = thisBoard.tileValToNum(diceResult);
    for (int curTile : tileNumLst) {
        int rss = thisBoard.getRssOnTile(curTile);
        std::vector<int> playerLst = thisBoard.getPlayersOnTile(curTile);
        std::vector<int> locationLst = thisBoard.getResLocOnTile(curTile);
        int idx = 0;
        for (int player : playerLst) {
            int level =
                allPlayers[player]->getResLevelOnVertex(locationLst[idx]);
            allPlayers[player]->modifiesResources(rss, level);
            ++idx;
        }
    }
}

void Game::saveGame() {
    std::string saveFile;
    while (true) {
        cin >> saveFile;

        std::ofstream file(saveFile);
        if (file.is_open()) {
            file << curPlayer << std::endl;
            for (size_t i = 0; i < allPlayers.size(); i++)
                file << allPlayers[i]->getData() << std::endl;

            file << thisBoard.getBoardData() << std::endl;
            file << thisBoard.whichHasGeese();

        } else {
            std::cout << "Unable to save file to " << saveFile << std::endl;
            std::cout << "Try another file." << saveFile << std::endl;
        }
    }
}