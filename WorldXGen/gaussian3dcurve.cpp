#include "gaussian3dcurve.h"

// ---- Gaussian3DCurve

Gaussian3DCurve::Gaussian3DCurve(float gShiftX, float gShiftY, float gSizeX, float gSizeY, float gSizeZ, float gTheta)
{
    this->gaussianShiftX    = gShiftX;
    this->gaussianShiftY    = gShiftY;
    this->gaussianSizeX     = gSizeX;
    this->gaussianSizeY     = gSizeY;
    this->gaussianSizeZ     = gSizeZ;
    this->theta             = gTheta;
}

float Gaussian3DCurve::getValue(float x, float y)
{

    float   a = powf(cosf(this->theta), 2.f) / (2 * powf(this->gaussianSizeX, 2.f)) + powf(sinf(this->theta), 2.f) / (2 * powf(this->gaussianSizeY, 2.f)),
            b = -sinf(2 * this->theta) / (4 * powf(this->gaussianSizeX, 2.f)) + sinf(2 * this->theta) / (4 * powf(this->gaussianSizeY, 2.f)),
            c = powf(sinf(this->theta), 2.f) / (2 * powf(this->gaussianSizeX, 2.f)) + powf(cosf(this->theta), 2.f) / (2 * powf(this->gaussianSizeY, 2.f));


    return expf(
        -(a * powf(x - this->gaussianShiftX, 2.f) + 2 * b * (x - this->gaussianShiftX) * (y - this->gaussianShiftY) + c * powf(y - this->gaussianShiftY, 2.f))
    ) * gaussianSizeZ;
}


// ---- Gaussian3DCurveBuilder

Gaussian3DCurveBuilder::Gaussian3DCurveBuilder()
{
    this->gaussianShiftX    = 0.;
    this->gaussianShiftY    = 0.;
    this->gaussianSizeX     = 1.;
    this->gaussianSizeY     = 1.;
    this->gaussianSizeZ     = 1.;
}


Gaussian3DCurveBuilder * Gaussian3DCurveBuilder::setGaussianShiftX(float gShiftX)
{
    this->gaussianShiftX = gShiftX;

    return this;
}

Gaussian3DCurveBuilder * Gaussian3DCurveBuilder::setGaussianShiftY(float gShiftY)
{
    this->gaussianShiftY = gShiftY;

    return this;
}

Gaussian3DCurveBuilder * Gaussian3DCurveBuilder::setGaussianSizeX(float gSizeX)
{
    this->gaussianSizeX = gSizeX;

    return this;
}

Gaussian3DCurveBuilder * Gaussian3DCurveBuilder::setGaussianSizeY(float gSizeY)
{
    this->gaussianSizeY = gSizeY;

    return this;
}

Gaussian3DCurveBuilder * Gaussian3DCurveBuilder::setGaussianSizeZ(float gSizeZ)
{
    this->gaussianSizeZ = gSizeZ;

    return this;
}

Gaussian3DCurveBuilder * Gaussian3DCurveBuilder::setTheta(float gTheta)
{
    this->theta = gTheta;

    return this;
}

Gaussian3DCurve * Gaussian3DCurveBuilder::make()
{
    return new Gaussian3DCurve(gaussianShiftX, gaussianShiftY, gaussianShiftX, gaussianShiftY, gaussianSizeZ, theta);
}
