#ifndef _BUILDER_H_
#define _BUILDER_H_

#include <vector>
#include "buildertype.h"
#include "residence.h"

class Builder {
    // the color of the builder (0 - blue, 1 - red, 2 - orange, 3 - yellow)
    int color;
    bool fairDice;  // truth value for the builder's dice being a fair dice
    std::vector<Residence> builtLst;  // a vector list of built residence
    /* a vector list of resources owned
     * Note that the vector list has only 5 fields, we specify the order as:
     * 0 - Brick, 1 - Energy, 2 - Glass, 3 - Heat, 4 - Wifi
     */
    std::vector<int> resources;

   public:
    // roll the dice (apply algorithms based on whether user has a fair dice)
    void rollDice();
    // if possible, upgrade the cuurent residence to the next level
    void upgradeResidence(int location);
    void printStatus();
    void printResidence();         // display built residence
    void buildRoad(int location);  // build a road at the location
    // build a residence(basement) at the location
    void buildResidence(int location);
    int calculatePoints();  // calculate owned building points
};

#endif