#ifndef GAUSSIAN3DCURVE_H
#define GAUSSIAN3DCURVE_H

#include <math.h>

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
    float theta;

    Gaussian3DCurve(float gShiftX, float gShiftY, float gSizeX, float gSizeY, float gSizeZ, float gtheta);

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
    float theta;

public:

    Gaussian3DCurveBuilder();

    Gaussian3DCurveBuilder * setGaussianShiftX(float gShiftX);
    Gaussian3DCurveBuilder * setGaussianShiftY(float gShiftY);
    Gaussian3DCurveBuilder * setGaussianSizeX(float gSizeX);
    Gaussian3DCurveBuilder * setGaussianSizeY(float gSizeY);
    Gaussian3DCurveBuilder * setGaussianSizeZ(float gSizeZ);
    Gaussian3DCurveBuilder * setTheta(float gTheta);

    Gaussian3DCurve * make();
};

#endif // GAUSSIAN3DCURVE_H
