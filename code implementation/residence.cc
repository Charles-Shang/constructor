#include "residence.h"
#include <string>

Residence::Residence(int _location, int _level, int _buildingPoints)
    : location{_location}, level{_level}, buildingPoints{_buildingPoints} {}

int Residence::getBuildingPoints() { return buildingPoints; }

void Residence::upgrade() {
    ++level;
    ++buildingPoints;
}

int Residence::getLevel() { return level; }

int Residence::getLocation() { return location; }

std::string Residence::getResType() {
    switch (level) {
        case 0:
            return "B";
        case 1:
            return "H";
        default:
            return "T";
    }
}

std::string formatInteger(int num) {
    std::string temp = "";
    if (num < 10) temp += " ";
    temp += std::to_string(num);
    return temp;
}

std::string Residence::getData() {
    std::string data = formatInteger(location) + " " + getResType();
    return data;
}

void Residence::clearRes() {
    level = 0;
    buildingPoints = 1;
}