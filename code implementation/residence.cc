#include "residence.h"
#include <string>

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

std::string Residence::getResType(){
    switch (level)
    {
    case 0:
        return "BASEMENT";
    case 1:
        return "HOUSE";
    default:
        return "TOWER";
    }
}