#ifndef CONICMOUNTAINMAPBUILDER_H
#define CONICMOUNTAINMAPBUILDER_H

#include <algorithm>
#include <random>
#include "random.h"
#include "mapbuilder.h"
#include "simplepeaksmoutainmapbuilder.h"
#include "map.h"

#define RANDOM_CURVES_COUNT_MIN 4
#define RANDOM_CURVES_COUNT_MAX 32
#define CURVE_HEIGHT_MAX        12

class SimplePeaksMoutainMapBuilder : public MapBuilder
{
public:

    /**
     * @brief The Gaussian3DCurve class is used to represent a gaussian curve in a 3D space.
     */
    class Gaussian3DCurve
    {
    public:
        float gaussianShiftX;
        float gaussianShiftY;
        float gaussianSizeX;
        float gaussianSizeY;
        float gaussianSizeZ;

        Gaussian3DCurve(float gShiftX, float gShiftY, float gSizeX, float gSizeY, float gSizeZ);

        float getValue(float x, float y);
    };

    /**
     * @brief The Gaussian3DCurveBuilder class is used to create a Gaussian3DCurve object using a Factory Pattern.
     */
    class Gaussian3DCurveBuilder
    {
    private:
        float gaussianShiftX;
        float gaussianShiftY;
        float gaussianSizeX;
        float gaussianSizeY;
        float gaussianSizeZ;

    public:

        Gaussian3DCurveBuilder();

        Gaussian3DCurveBuilder * setGaussianShiftX(float gShiftX);
        Gaussian3DCurveBuilder * setGaussianShiftY(float gShiftY);
        Gaussian3DCurveBuilder * setGaussianSizeX(float gSizeX);
        Gaussian3DCurveBuilder * setGaussianSizeY(float gSizeY);
        Gaussian3DCurveBuilder * setGaussianSizeZ(float gSizeZ);

        Gaussian3DCurve * make();
    };

    SimplePeaksMoutainMapBuilder();
    SimplePeaksMoutainMapBuilder * addGaussianCurve(SimplePeaksMoutainMapBuilder::Gaussian3DCurve * curve);
    Map * build();
    Map * build(bool randomCurves);

private:
    vector<Gaussian3DCurve *> curves;
};

#endif // CONICMOUNTAINMAPBUILDER_H
