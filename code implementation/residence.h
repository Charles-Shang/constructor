#ifndef _RESIDENCE_H_
#define _RESIDENCE_H_

#include <string>

class Residence {
    int location;
    int level;  // the level of residence (0 - basement, 1 - house, 2 - tower)
    int buildingPoints;  // the building points associated with level

   public:
    Residence(int _location, int _level = 0, int _buildingPoints = 1);
    int getLocation();
    std::string getResType();
    void clearRes();





    // upgrade the cuurent residence to the next level
    void upgrade();
    int getBuildingPoints();
    int getLevel();

    
    std::string getData();
};

#endif