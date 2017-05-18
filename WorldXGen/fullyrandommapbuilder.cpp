#include "fullyrandommapbuilder.h"

Map * FullyRandomMapBuilder::build()
{
    Map * generatedMap = new Map(this->sizeX, this->sizeY);

    for (unsigned int x; x < this->sizeX; ++x) {
        for (unsigned int y; y <  this->sizeY; ++y) {
            Point3D * point = generatedMap->getPoint(x, y);

            point->setZ(Random::uniformDistribution());
        }
    }

    return generatedMap;
}
