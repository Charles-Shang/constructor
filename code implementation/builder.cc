#include "builder.h"

Builder::Builder(int _colour, std::default_random_engine _rng)
    : colour{_colour}, fairDice{false}, seed{_rng} {}

std::string Builder::getBuilderName() {
    switch (colour) {
        case 0:
            return "BLUE";
        case 1:
            return "RED";
        case 2:
            return "ORANGE";
        default:
            return "YELLOW";
    }
}

void Builder::buildResidence(int location, bool first) {
    Residence newResidence{location};
    builtLst.emplace_back(newResidence);
    if (!first) {
        resources[0]--;
        resources[1]--;
        resources[2]--;
        resources[4]--;
    }
}

std::string Builder::colourShortName() {
    switch (colour) {
        case 0:
            return "B";
        case 1:
            return "R";
        case 2:
            return "O";
        default:
            return "Y";
    }
}

std::string Builder::getResDisplay(int location, std::string type) {
    std::string data = "";
    if (type == "residence") {
        for (auto residence : builtLst) {
            if (residence.getLocation() == location) {
                data += colourShortName() + residence.getResType();
                return data;
            }
        }
    } else {
        for (auto road : roadLst) {
            if (road == location) {
                data += colourShortName() + "R";
                return data;
            }
        }
    }

    if (location <= 9) data += " ";
    data += std::to_string(location);
    return data;
}