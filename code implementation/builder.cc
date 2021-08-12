#include "builder.h"

int Builder::getColour() { return colour; }

// void Builder::rollDice() {}

int Builder::upgradeResidence(int location) {
    int idx = 0;
    for (auto res : builtLst) {
        if (res.getLocation() == location) {
            res.upgrade();
            return idx;
        }
        ++idx;
    }
}

void Builder::printStatus() {}

void Builder::printResidence() {}

void Builder::printRecentUpgrade(int idx) {
    std::cout << builtLst[idx].getLevel();
}

void Builder::buildRoad(int location) {
    roadLst.emplace_back(location);
    resources[3] -= 1;
    resources[4] -= 1;
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
    return (resources[0] >= 1 && resources[1] >= 1 && resources[2] >= 1 &&
            resources[4] >= 1);
}

bool Builder::canBuildRoad() {
    return (resources[3] >= 1 && resources[4] >= 1);
}

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
    int length = builtLst.size();
    for (int i = 0; i < length; ++i) {
        if (builtLst[i].getLocation() == location) {
            return true;
        }
    }
}

bool Builder::highestLevel(int location) {
    return builtLst[location].getLevel() == 2;
}