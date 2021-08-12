#ifndef _RESIDENCE_H_
#define _RESIDENCE_H_

#include "residencetype.h";

class Residence {
    int location;
    int level;  // the level of residence (0 - basement, 1 - house, 2 - tower)
    int buildingPoints;  // the building points associated with level

   public:
    // upgrade the cuurent residence to the next level
    void upgrade();
    int getBuildingPoints();
    int getLevel();
    int getLocation();
};

#endif