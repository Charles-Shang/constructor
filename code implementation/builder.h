#ifndef _BUILDER_H_
#define _BUILDER_H_

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "residence.h"

class Builder {
    // the color of the builder (0 - blue, 1 - red, 2 - orange, 3 - yellow)
    int colour;
    bool fairDice;  // truth value for the builder's dice being a fair dice
    std::default_random_engine seed;
    std::vector<Residence> builtLst;  // a vector list of built residence
    std::vector<int> roadLst;
    /* a vector list of resources owned
     * Note that the vector list has only 5 fields, we specify the order as:
     * 0 - Brick, 1 - Energy, 2 - Glass, 3 - Heat, 4 - Wifi
     */
    std::vector<int> resources;

   public:
    Builder(int _colour, std::default_random_engine _rng);
    std::string getBuilderName();
    void buildResidence(int location, bool first = false);
    std::string colourShortName();
    std::string getResDisplay(int location, std::string type);
    int calculatePoints();

    void switchFairDice(bool state);
    int rollDice();

    int calculateResouceSum();
    std::vector<int> listAllRss();
    void modifiesResources(int resType, int delta);

    void printStatus();
    void printResidence();         // display built residence

    // determine if the builder have enough resources to build a residence
    bool haveEnoughRssForResidence();
    // determine if the builder have enough resources to build a road
    bool haveEnoughRssForRoad();

};

#endif