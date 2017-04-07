#include "map.h"

Map::Map(int sizeX, int sizeY)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->points = vector<Point3D *>(sizeX * sizeY);

    for (unsigned int x = 0; x < sizeX; ++x)
    {
        for (unsigned int y = 0; y < sizeY; ++y)
        {
            this->points.push_back(new Point3D(x, y, 0.));
        }
    }
}

Point3D * Map::getPoint(int x, int y)
{
    Point3D * foundPoint = nullptr;

    for (unsigned int i = 0; i < this->points.size() && foundPoint == nullptr; ++i)
    {
        Point3D * curPoint = this->points[i];

        if (curPoint->getX() == x && curPoint->getY() == y)
        {
            foundPoint = curPoint;
            // The loop will end when this variable will
            // get a different value than nullptr.
        }
    }

    return foundPoint;
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
