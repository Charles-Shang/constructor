#include "residence.h"

Residence::Residence (int _location, int _level, int _buildingPoints) 
: location{_location}, level{_level}, buildingPoints{_buildingPoints} {}

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