#include "builder.h"

Builder::Builder(std::default_random_engine _rng) : seed{_rng} {}

int Builder::getColour() { return colour; }

std::string Builder::getColourName() {
    switch (colour) {
        case 0:
            return "Blue";
        case 1:
            return "Red";
        case 2:
            return "Orange";
        default:
            return "Yellow";
    }
}

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
            }

            if (2 <= rollNum && rollNum <= 12)
                return rollNum;
            else
                std::cout << "Invalid roll" << std::endl;
        }
    }
}

void Builder::switchFairDice(bool state) { fairDice = state; }

// assume the residece at location is belong to the builder
std::string Builder::upgradeResidence(int location) {
    for (auto residence : builtLst) {
        if (residence.getLocation() == location) {
            residence.upgrade();
            return residence.getResType();
        }
    }
}

void Builder::printStatus() {
    std::cout << getColourName() << " has " << calculatePoints()
              << " building points, " << resources[0] << " brick, "
              << resources[1] << " energy, " << std::endl;
    std::cout << resources[2] << " glass, " << resources[3] << " head, and "
              << resources[3] << "WiFi." << std::endl;
}

void Builder::printResidence() {
    std::cout << getColourName() << " has built:" << std::endl;
    for (auto res : builtLst)
        std::cout << res.getLocation() << " " << res.getResType() << std::endl;
}

void Builder::printRecentUpgrade(int idx) {
    std::cout << builtLst[idx].getLevel();
}

void Builder::buildRoad(int location) {
    roadLst.emplace_back(location);
    resources[3]--;
    resources[4]--;
}

void Builder::buildResidence(int location, bool first) {
    Residence newResidence{location, 0, 1};
    builtLst.emplace_back(newResidence);
    if (!first) {
        resources[0] -= 1;
        resources[1] -= 1;
        resources[2] -= 1;
        resources[4] -= 1;
    }
}

int Builder::calculatePoints() {
    int point = 0;
    for (Residence res : builtLst) {
        point += res.getBuildingPoints();
    }
    return point;
}

bool Builder::canBuildResidence() {
    return (resources[0] && resources[1] && resources[2] && resources[4]);
}

bool Builder::canBuildRoad() { return (resources[3] && resources[4]); }

bool Builder::canUpgrade(int location) {
    if (builtLst[location].getLevel() == 0) {
        return (resources[2] >= 2 && resources[3] >= 3);
    } else if (builtLst[location].getLevel() == 1) {
        return (resources[0] >= 3 && resources[1] >= 2);
    } else {
        return false;
    }
}

bool Builder::haveResidence(int location) {
    for (size_t i = 0; i < builtLst.size(); i++)
        if (builtLst[i].getLocation() == location) return true;

    return false;
}

bool Builder::highestLevel(int location) {
    return builtLst[location].getLevel() == 2;
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

int Builder::calculateResouceSum() {
    int sum = 0;
    for (int i : resources) sum += i;
    return sum;
}

void Builder::modifiesResources(int res, int add) { resources[res] += add; }

std::vector<int> Builder::listAllRss() {
    std::vector<int> rssLst;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < resources[i]; j++) {
            rssLst.emplace_back(i);
        }
    }

    return rssLst;
}

int Builder::getResLevelOnVertex(int vertexNum) {
    for (auto res : builtLst) {
        if (res.getLocation() == vertexNum) {
            return res.getBuildingPoints();
        }
    }
}