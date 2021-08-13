#include "builder.h"

Builder::Builder(int _colour, std::default_random_engine _rng)
    : colour{_colour}, fairDice{false}, seed{_rng} {}

std::string Builder::getBuilderName() {
    switch (colour) {
        case 0:
            return "BLUE";
        case 1:
            return "RED";
        case 2:
            return "ORANGE";
        default:
            return "YELLOW";
    }
}

void Builder::buildResidence(int location, bool first) {
    Residence newResidence{location};
    builtLst.emplace_back(newResidence);
    if (!first) {
        resources[0]--;
        resources[1]--;
        resources[2]--;
        resources[4]--;
    }
}

std::string Builder::colourShortName() {
    switch (colour) {
        case 0:
            return "B";
        case 1:
            return "R";
        case 2:
            return "O";
        default:
            return "Y";
    }
}

std::string Builder::getResDisplay(int location, std::string type) {
    std::string data = "";
    if (type == "residence") {
        for (auto residence : builtLst) {
            if (residence.getLocation() == location) {
                data += colourShortName() + residence.getResType();
                return data;
            }
        }
    } else {
        for (auto road : roadLst) {
            if (road == location) {
                data += colourShortName() + "R";
                return data;
            }
        }
    }

    if (location <= 9) data += " ";
    data += std::to_string(location);
    return data;
}

int Builder::calculatePoints() {
    int point = 0;
    for (Residence res : builtLst) {
        point += res.getBuildingPoints();
    }
    return point;
}

void Builder::switchFairDice(bool state) { fairDice = state; }

int Builder::rollDice() {
    if (fairDice) {
        std::vector<int> diceValue = {1, 2, 3, 4, 5, 6};
        std::shuffle(diceValue.begin(), diceValue.end(), seed);
        int a = diceValue[0];
        std::shuffle(diceValue.begin(), diceValue.end(), seed);
        int b = diceValue[0];
        return a + b;
    } else {
        while (true) {
            std::cout << "Input a roll between 2 and 12:" << std::endl;
            int rollNum;

            try {
                std::cin >> rollNum;
            } catch (std::ios::failure &) {
                std::cout << "Invalid roll" << std::endl;
                std::cin.clear();
                std::cin.ignore();
                continue;
            }

            if (2 <= rollNum && rollNum <= 12)
                return rollNum;
            else
                std::cout << "Invalid roll" << std::endl;
        }
    }
}

int Builder::calculateResouceSum() {
    int sum = 0;
    for (int i : resources) sum += i;
    return sum;
}

std::vector<int> Builder::listAllRss() {
    std::vector<int> rssLst;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < resources[i]; j++) {
            rssLst.emplace_back(i);
        }
    }

    return rssLst;
}

void Builder::modifiesResources(int resType, int delta) {
    resources[resType] += delta;
}

void Builder::printStatus() {
    std::cout << getBuilderName() << " has " << calculatePoints()
              << " building points, " << resources[0] << " brick, "
              << resources[1] << " energy, ";
    std::cout << resources[2] << " glass, " << resources[3] << " head, and "
              << resources[3] << " WiFi." << std::endl;
}

void Builder::printResidence() {
    std::cout << getBuilderName() << " has built:" << std::endl;
    for (auto res : builtLst)
        std::cout << res.getLocation() << " " << res.getResType() << std::endl;
}

bool Builder::haveEnoughRssForResidence() {
    return resources[0] > 0 && resources[1] > 0 && resources[2] > 0 &&
           resources[4] > 0;
}

bool Builder::haveEnoughRssForRoad() {
    return resources[3] > 0 && resources[4] > 0;
}

bool Builder::haveRssForImprove(int location) {
    int level;
    for (auto single : builtLst) {
        if (single.getLocation() == location) {
            level = single.getLevel();
            break;
        }
    }

    if (level == 2) {
        return resources[2] >= 2 && resources[3] >= 3;
    } else {
        return resources[0] >= 3 && resources[1] >= 2 && resources[2] >= 1 &&
               resources[4] >= 1;
    }
}

bool Builder::highestLevel(int location) {
    int level;
    for (auto single : builtLst) {
        if (single.getLocation() == location) {
            level = single.getLevel();
            break;
        }
    }
    return level == 2;
}

bool Builder::haveResidence(int location) {
    for (auto single : builtLst) {
        if (single.getLocation() == location) {
            return true;
        }
    }

    return false;
}

// assume the residece at location is belong to the builder
std::string Builder::upgradeResidence(int location) {
    for (auto residence : builtLst) {
        if (residence.getLocation() == location) {
            residence.upgrade();
            return residence.getResType();
        }
    }

    return "you should not see this";  // this should not be reached
}
int Builder::getResLevelOnVertex(int vertexNum) {
    for (auto res : builtLst) {
        if (res.getLocation() == vertexNum) {
            return res.getBuildingPoints();
        }
    }
    return 99999;  // this should not be reached
}

int Builder::getNumOfRssOf(int type) { return resources[type]; }

void Builder::trade(int give, int take) {
    resources[give]--;
    resources[take]++;
}

std::string Builder::getData() {
    std::string data = "";
    for (size_t i = 0; i < resources.size(); i++) data += resources[i] + " ";
    data += "r ";
    for (size_t i = 0; i < roadLst.size(); i++) data += roadLst[i] + " ";
    data += "h";
    for (size_t i = 0; i < builtLst.size(); i++)
        data += " " + builtLst[i].getData();

    return data;
}