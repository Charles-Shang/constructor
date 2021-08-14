#ifndef _RESIDENCE_H_
#define _RESIDENCE_H_

#include <string>

class Residence {
    int location;
    int level;  // the level of residence (0 - basement, 1 - house, 2 - tower)
    int buildingPoints;  // the building points associated with level

   public:
    Residence(int _location, int _level = 0, int _buildingPoints = 1);
    int getLocation();         // get the location of the residence
    std::string getResType();  // get the type of the residence
    void clearRes();           // clear the residence when start a new game

    // upgrade the curent residence to the next level
    void upgrade();
    int getBuildingPoints();
    int getLevel();

    void setType(std::string type);

    std::string getData();
};

#endif