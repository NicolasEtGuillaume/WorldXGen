#include "fullyrandommapbuilder.h"

Map * FullyRandomMapBuilder::build()
{
    srand(this->seed->getValue());

    Map * generatedMap = new Map(this->sizeX, this->sizeY);

    for (unsigned int x = 0; x < this->sizeX; ++x) {
        for (unsigned int y = 0; y <  this->sizeY; ++y) {
            Point3D * point = generatedMap->getPoint(x, y);

            point->setZ(Random::uniformDistribution());
        }
    }

    return generatedMap;
}
