#ifndef MAP_H
#define MAP_H


class Map
{
private:
    // TODO: Add the Points3Ds' array.
    string name;
    int sizeX;
    int sizeY;

public:
    Map();

    Point3D getPoint(int x, int y);

    string getName();
    int getSizeX();
    int getSizeY();
};

#endif // MAP_H
