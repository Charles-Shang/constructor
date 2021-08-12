#include "builder.h"

int Builder::getColour() { return colour; }

// void Builder::rollDice() {}

void Builder::upgradeResidence(int location) { builtLst[location].upgrade(); }

// void Builder::printStatus(){}

// void Builder::printResidence(){}

// void Builder::buildRoad(int location){}

// void Builder::buildResidence(int location) {
    
// }

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