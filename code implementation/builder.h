#ifndef _BUILDER_H_
#define _BUILDER_H_

#include <algorithm>
#include <iostream>
#include <vector>
#include "buildertype.h"
#include "residence.h"

class Builder {
    unsigned seed;
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
    Builder(unsigned _seed);
    int getColour();
    std::string getColourName();
    // roll the dice (apply algorithms based on whether user has a fair dice)
    int rollDice();
    void switchFairDice(bool state);
    // if possible, upgrade the cuurent residence to the next level
    // return the type of the upgraded residence in builtLst
    std::string upgradeResidence(int location);
    void printStatus();
    void printResidence();         // display built residence
    void buildRoad(int location);  // build a road at the location
    // build a residence(basement) at the location
    void buildResidence(int location, bool first);
    int calculatePoints();  // calculate owned building points
    // determine if the builder have enough resources to build a residence
    bool canBuildResidence();
    // determine if the builder have enough resources to build a road
    bool canBuildRoad();
    // determine if the builder have enough resources to upgrade the residence
    bool canUpgrade(int location);
    // determine if the builder have a residence at the location
    bool haveResidence(int location);
    bool highestLevel(int location);
    // print the most recent upgraded residence's level
    void printRecentUpgrade(int idx);
    void trade(int give, int take);

    std::string getData();
};

#endif