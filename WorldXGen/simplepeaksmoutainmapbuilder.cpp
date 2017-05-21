#include "simplepeaksmoutainmapbuilder.h"

Map * SimplePeaksMoutainMapBuilder::build()
{
    Map * generatedMap = new Map(this->sizeX, this->sizeY);

    unsigned int centerXpos = this->sizeX / 2;
    unsigned int centerYpos = this->sizeY / 2;

    Point3D * centerPoint = generatedMap->getPoint(centerXpos, centerYpos);

    float centerPosHeight = abs(Random::normalDistribution(this->seed->getValue()) * 4);
    centerPoint->setZ(centerPosHeight);

    vector<Point3D *> points = *(generatedMap->getAllPoints());

    unsigned int maxSize = max(this->sizeX, this->sizeY);

    for (unsigned int radius = 1; radius < maxSize / 2; ++radius)
    {
        for (Point3D * point : points)
        {
            float distance = sqrt(
                pow(point->getX() - centerPoint->getX(), 2) +
                pow(point->getY() - centerPoint->getY(), 2)
            );

            if (radius - 1 < distance && distance <= radius)
            {
                float height = (float) max(0., centerPosHeight - distance * Random::normalDistribution(this->seed->getValue()) / 10.);
                point->setZ(height);
            }
        }
    }

    return generatedMap;
}
