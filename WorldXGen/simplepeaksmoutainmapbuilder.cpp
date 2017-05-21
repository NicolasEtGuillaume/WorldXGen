#include "simplepeaksmoutainmapbuilder.h"

Map * SimplePeaksMoutainMapBuilder::build()
{
    Map * generatedMap = new Map(this->sizeX, this->sizeY);

    vector<Point3D *> points = *(generatedMap->getAllPoints());

    for (Point3D * point : points) { point->setZ(getGaussianValue(point->getX(), point->getY())); }

    return generatedMap;
}

SimplePeaksMoutainMapBuilder * SimplePeaksMoutainMapBuilder::setGaussianFunctionParams(float gShiftX, float gShiftY, float gSizeX, float gSizeY)
{
    this->gaussianShiftX    = gShiftX;
    this->gaussianShiftY    = gShiftY;
    this->gaussianSizeX     = gSizeX;
    this->gaussianSizeY     = gSizeY;

    return this;
}

SimplePeaksMoutainMapBuilder * SimplePeaksMoutainMapBuilder::setGaussianFunctionShift(float gShiftX, float gShiftY)
{
    this->gaussianShiftX = gShiftX;
    this->gaussianShiftY = gShiftY;

    return this;
}

SimplePeaksMoutainMapBuilder * SimplePeaksMoutainMapBuilder::setGaussianFunctionShiftX(float gShiftX)
{
    this->gaussianShiftX = gShiftX;

    return this;
}

SimplePeaksMoutainMapBuilder * SimplePeaksMoutainMapBuilder::setGaussianFunctionShiftY(float gShiftY)
{
    this->gaussianShiftY = gShiftY;

    return this;
}

SimplePeaksMoutainMapBuilder * SimplePeaksMoutainMapBuilder::setGaussianFunctionSize(float gSizeX, float gSizeY)
{
    this->gaussianSizeX = gSizeX;
    this->gaussianSizeY = gSizeY;

    return this;
}

SimplePeaksMoutainMapBuilder * SimplePeaksMoutainMapBuilder::setGaussianFunctionSizeX(float gSizeX)
{
    this->gaussianSizeX = gSizeX;

    return this;
}

SimplePeaksMoutainMapBuilder * SimplePeaksMoutainMapBuilder::setGaussianFunctionSizeY(float gSizeY)
{
    this->gaussianSizeY = gSizeY;

    return this;
}

float SimplePeaksMoutainMapBuilder::getGaussianValue(float x, float y)
{
    return exp(
        -(pow(x - gaussianShiftX, 2) / pow(2 * gaussianSizeX, 2)) - pow(y - gaussianShiftY, 2) / pow(2 * gaussianSizeY, 2)
    );
}
