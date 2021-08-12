#include "builder.h"

int Builder::getColour() {
    return colour;
}

void Builder::rollDice() {}

void Builder::upgradeResidence(int location) {
    builtLst[location].upgrade();

}

void Builder::printStatus(){}

void Builder::printResidence(){}

void Builder::buildRoad(int location){}

void Builder::buildResidence(int location) {
    
}

int Builder::calculatePoints() {
    int point = 0;
    for (Residence res : builtLst) {
        point += res.getBuildingPoints();
    }
    return point;
}
