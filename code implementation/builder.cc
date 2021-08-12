#include "builder.h"

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

// void Builder::rollDice() {}

// assume the residece at location is belong to the builder
std::string Builder::upgradeResidence(int location) {
    for (auto residence : builtLst) {
        if (residence.getLocation() == location) {
            residence.upgrade();
            return residence.getResType();
        }
    }
}

void Builder::printStatus() {}

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

void Builder::buildResidence(int location) {
    Residence newResidence{location, 0, 1};
    builtLst.emplace_back(newResidence);
    resources[0] -= 1;
    resources[1] -= 1;
    resources[2] -= 1;
    resources[4] -= 1;
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