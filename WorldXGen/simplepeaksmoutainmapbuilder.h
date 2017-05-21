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
    void setGaussianFunctionParams(float gShiftX, float gShiftY, float gSizeX, float gSizeY);
    void setGaussianFunctionShift(float gShiftX, float gShiftY);
    void setGaussianFunctionShiftX(float gShiftX);
    void setGaussianFunctionShiftY(float gShiftY);
    void setGaussianFunctionSize(float gSizeX, float gSizeY);
    void setGaussianFunctionSizeX(float gSizeX);
    void setGaussianFunctionSizeY(float gSizeY);

    Map * build();
};

#endif // CONICMOUNTAINMAPBUILDER_H
