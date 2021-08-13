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
    return (resources[0] && resources[1] && resources[2] && resources[4]);
}

bool Builder::haveEnoughRssForRoad() { return (resources[3] && resources[4]); }

int Builder::getResLevelOnVertex(int vertexNum) {
    for (auto res : builtLst) {
        if (res.getLocation() == vertexNum) {
            return res.getBuildingPoints();
        }
    }
    return 99999; // this should not be reached
}