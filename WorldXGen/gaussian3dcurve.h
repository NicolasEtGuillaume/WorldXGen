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

    /**
     * @brief Returns the height at the given location.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return The z coordinate corresponding to the x and y.
     */
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

    /**
     * @brief Sets the curve's location in the x coordinate.
     * @param gShiftX The x coordinate.
     * @return Itself, the same Gaussian3DCurveBuilder instance (Factory pattern).
     */
    Gaussian3DCurveBuilder * setGaussianShiftX(float gShiftX);

    /**
     * @brief Sets the curve's location in the y coordinate.
     * @param gShiftY The y coordinate.
     * @return Itself, the same Gaussian3DCurveBuilder instance (Factory pattern).
     */
    Gaussian3DCurveBuilder * setGaussianShiftY(float gShiftY);

    /**
     * @brief Sets the size in the x axis.
     * @param gSizeX The size in the x axis.
     * @return Itself, the same Gaussian3DCurveBuilder instance (Factory pattern).
     */
    Gaussian3DCurveBuilder * setGaussianSizeX(float gSizeX);

    /**
     * @brief Sets the size in the y axis.
     * @param gSizeY The size in the y axis.
     * @return Itself, the same Gaussian3DCurveBuilder instance (Factory pattern).
     */
    Gaussian3DCurveBuilder * setGaussianSizeY(float gSizeY);

    /**
     * @brief Sets the size in the z axis (height).
     * @param gSizeZ The height.
     * @return Itself, the same Gaussian3DCurveBuilder instance (Factory pattern).
     */
    Gaussian3DCurveBuilder * setGaussianSizeZ(float gSizeZ);

    /**
     * @brief Sets the rotation of the curve.
     * @param gTheta The angle in radians.
     * @return Itself, the same Gaussian3DCurveBuilder instance (Factory pattern).
     */
    Gaussian3DCurveBuilder * setTheta(float gTheta);

    /**
     * @brief Instanciates a Gaussian3DCurve object with the parameters previously set.
     * @return The curve instance address.
     */
    Gaussian3DCurve * make();
};

#endif // GAUSSIAN3DCURVE_H
