#include "residence.h"

int Residence::getBuildingPoints() {
    return buildingPoints;
}

void Residence::upgrade() {
    ++level;
    ++buildingPoints;
}

int Residence::getLevel() {
    return level;
}

int Residence::getLocation() {
    return location;
}