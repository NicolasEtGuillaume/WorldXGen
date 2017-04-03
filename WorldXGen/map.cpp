#include "map.h"

Map::Map(int sizeX, int sizeY)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
}

Point3D Map::getPoint(int x, int y)
{
    // TODO: Return the correct point.
    return nullptr;
}

string Map::getName()
{
    return this->name;
}

int Map::getSizeX()
{
    return this->sizeX;
}

int Map::getSizeY()
{
    return this->sizeY;
}
