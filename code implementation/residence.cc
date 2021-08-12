#include "residence.h"

int Residence::getBuildingPoints() {
    return buildingPoints;
}

void Residence::upgrade() {
    ++level;
    ++buildingPoints;
}