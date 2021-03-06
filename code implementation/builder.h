#ifndef _BUILDER_H_
#define _BUILDER_H_

#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <vector>
#include "residence.h"

class Builder {
    // the color of the builder (0 - blue, 1 - red, 2 - orange, 3 - yellow)
    int colour;
    bool fairDice;  // truth value for the builder's dice being a fair dice
    std::default_random_engine seed;
    // a vector list of built residence
    std::vector<std::shared_ptr<Residence>> builtLst;
    std::vector<int> roadLst;
    /* a vector list of resources owned
     * Note that the vector list has only 5 fields, we specify the order as:
     * 0 - Brick, 1 - Energy, 2 - Glass, 3 - Heat, 4 - Wifi
     */
    std::vector<int> resources;

   public:
    Builder(int _colour, std::default_random_engine _rng);
    std::string getBuilderName();
    // build residence at location, if it is the first time build residence then
    // there is no resources deduct
    void buildResidence(int location, bool first = false);
    std::string colourShortName();
    std::string getResOrRoadDisplay(int location, std::string type);
    // calculate the points of a builder currently has
    int calculatePoints();

    // switch between fair dice and loaded dice
    void switchFairDice(bool state);
    // roll a dice
    int rollDice();

    // returns the sum of all resources
    int calculateResouceSum();
    std::vector<int> listAllRss();
    // modifies resources by delta
    void modifiesResources(int resType, int delta);

    // print information
    void printStatus();
    void printResidence();  // display built residence

    // determine if the builder have enough resources to build a residence
    bool haveEnoughRssForResidence();

    bool haveRssForImprove(int location);

    // determine if the builder have enough resources to build a road
    bool haveEnoughRssForRoad();

    // if possible, upgrade the cuurent residence to the next level
    // return the type of the upgraded residence in builtLst
    std::string upgradeResidence(int location);

    int getResLevelOnVertex(int vertexNum);

    bool highestLevel(int location);

    bool haveResidence(int location);

    bool haveRoad(int location);

    int getNumOfRssOf(int type);
    void buildRoad(int roadNum);
    void trade(int give, int take);

    std::string getData();
    void clearBuilder();

    // For load command
    void setRss(int index, int value);  // set resouces add it
    void setRoads(int locations);       // add location of roads built
    void addResidence(int location, std::string type);  // add residence built

    std::vector<int> getRoadLst();
    std::vector<int> getResidenceLst();
};

#endif
