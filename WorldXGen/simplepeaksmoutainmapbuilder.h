#ifndef CONICMOUNTAINMAPBUILDER_H
#define CONICMOUNTAINMAPBUILDER_H

#include <algorithm>
#include "random.h"
#include "mapbuilder.h"
#include "map.h"

class SimplePeaksMoutainMapBuilder : public MapBuilder
{
private:
    float gaussianShiftX;
    float gaussianShiftY;
    float gaussianSizeX;
    float gaussianSizeY;

    float getGaussianValue(float x, float y);

public:
    SimplePeaksMoutainMapBuilder * setGaussianFunctionParams(float gShiftX, float gShiftY, float gSizeX, float gSizeY);
    SimplePeaksMoutainMapBuilder * setGaussianFunctionShift(float gShiftX, float gShiftY);
    SimplePeaksMoutainMapBuilder * setGaussianFunctionShiftX(float gShiftX);
    SimplePeaksMoutainMapBuilder * setGaussianFunctionShiftY(float gShiftY);
    SimplePeaksMoutainMapBuilder * setGaussianFunctionSize(float gSizeX, float gSizeY);
    SimplePeaksMoutainMapBuilder * setGaussianFunctionSizeX(float gSizeX);
    SimplePeaksMoutainMapBuilder * setGaussianFunctionSizeY(float gSizeY);

    Map * build();
};

#endif // CONICMOUNTAINMAPBUILDER_H
