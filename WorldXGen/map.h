#ifndef MAP_H
#define MAP_H

#include <string>
#include "point3d.h"

using namespace std;

class Map
{
private:
    // TODO: Add the Points3Ds' array.
    string name;
    int sizeX;
    int sizeY;

public:
    Map(int sizeX, int sizeY);

    Point3D * getPoint(int x, int y);

    string getName();
    int getSizeX();
    int getSizeY();
};

#endif // MAP_H
