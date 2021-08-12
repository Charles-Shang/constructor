#ifndef _BUILDER_H_
#define _BUILDER_H_

#include <vector>
#include "buildertype.h"
#include "residence.h"
#include <algorithm>
#include <iostream>

class Builder {
    // the color of the builder (0 - blue, 1 - red, 2 - orange, 3 - yellow)
    int colour;
    bool fairDice;  // truth value for the builder's dice being a fair dice
    std::vector<Residence> builtLst;  // a vector list of built residence
    std::vector<int> roadLst;
    /* a vector list of resources owned
     * Note that the vector list has only 5 fields, we specify the order as:
     * 0 - Brick, 1 - Energy, 2 - Glass, 3 - Heat, 4 - Wifi
     */
    std::vector<int> resources;

   public:
    int getColour();
    std::string getColourName();    
    // roll the dice (apply algorithms based on whether user has a fair dice)
    void rollDice();
    // if possible, upgrade the cuurent residence to the next level
    int upgradeResidence(int location); // return the idx of the residence in builtLst
    void printStatus();
    void printResidence();         // display built residence
    void buildRoad(int location);  // build a road at the location
    // build a residence(basement) at the location
    void buildResidence(int location);
    int calculatePoints();     // calculate owned building points
    bool canBuildResidence();  // determine if the builder have enough resources
                               // to build a residence
    bool canBuildRoad();  // determine if the builder have enough resources to
                          // build a road
    bool canUpgrade(
        int location);  // determine if the builder have enough resources to
                        // upgrade the residence at location
    bool haveResidence(int location);  // determine if the builder have a
                                       // residence at the location
    bool highestLevel(int location);
    void printRecentUpgrade(int idx);  // print the most recent upgraded residence's level
};

#endif