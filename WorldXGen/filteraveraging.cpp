#include "filteraveraging.h"

FilterAveraging::FilterAveraging()
{

}

Map * FilterAveraging::apply(Map * oldMap)
{
    unsigned int    mapSizeX = oldMap->getSizeX(),
                    mapSizeY = oldMap->getSizeY();

    Map * newMap = new Map(mapSizeX, mapSizeY);
    vector<Point3D *> * oldPoints = oldMap->getAllPoints();

    for (Point3D * oldPoint : *oldPoints)
    {
        float   x = oldPoint->getX(),
                y = oldPoint->getY(),
                z = oldPoint->getZ();

        Point3D * newPoint = newMap->getPoint((unsigned int) x, (unsigned int) y);

        float newZ = z;

        newZ += oldMap->getPoint(
                    (unsigned int) min(x + 1, mapSizeX - 1.f),
                    (unsigned int) y
        )->getZ();

        newZ += oldMap->getPoint(
                    (unsigned int) max(x - 1, 0.f),
                    (unsigned int) y
        )->getZ();

        newZ += oldMap->getPoint(
                    (unsigned int) x,
                    (unsigned int) min(y + 1, mapSizeY - 1.f)
        )->getZ();

        newZ += oldMap->getPoint(
                    (unsigned int) x,
                    (unsigned int) max(y - 1, 0.f)
        )->getZ();

        newZ /= 5.f;

        newPoint->setZ(newZ);

    }

    return newMap;
}
