#include "simplepeaksmoutainmapbuilder.h"

SimplePeaksMoutainMapBuilder::SimplePeaksMoutainMapBuilder()
{

}

SimplePeaksMoutainMapBuilder * SimplePeaksMoutainMapBuilder::addGaussianCurve(SimplePeaksMoutainMapBuilder::Gaussian3DCurve * curve)
{
    this->curves.push_back(curve);

    return this;
}

Map * SimplePeaksMoutainMapBuilder::build()
{
    Map * generatedMap = new Map(this->sizeX, this->sizeY);

    vector<Point3D *> points = *(generatedMap->getAllPoints());

    for (Point3D * point : points)
    {
        bool firstOne = true;
        float finalZValue;

        for (SimplePeaksMoutainMapBuilder::Gaussian3DCurve * curve : this->curves)
        {
            float curveValue = curve->getValue(point->getX(), point->getY());

            if (firstOne) {
                finalZValue = curveValue;
                firstOne = false;
            } else {
                finalZValue = max(finalZValue, curveValue);
            }
        }
        point->setZ(finalZValue);
    }

    return generatedMap;
}

/*
 * Gaussian3DCurve
 */

SimplePeaksMoutainMapBuilder::Gaussian3DCurve::Gaussian3DCurve(float gShiftX, float gShiftY, float gSizeX, float gSizeY, float gSizeZ)
{
    this->gaussianShiftX    = gShiftX;
    this->gaussianShiftY    = gShiftY;
    this->gaussianSizeX     = gSizeX;
    this->gaussianSizeY     = gSizeY;
    this->gaussianSizeZ     = gSizeZ;
}

float SimplePeaksMoutainMapBuilder::Gaussian3DCurve::getValue(float x, float y)
{
    return exp(
        -(pow(x - gaussianShiftX, 2) / pow(2 * gaussianSizeX, 2)) - pow(y - gaussianShiftY, 2) / pow(2 * gaussianSizeY, 2)
    ) * gaussianSizeZ;
}


/*
 * Gaussian3DCurveBuilder
 */

SimplePeaksMoutainMapBuilder::Gaussian3DCurveBuilder::Gaussian3DCurveBuilder()
{
    this->gaussianShiftX    = 0.;
    this->gaussianShiftY    = 0.;
    this->gaussianSizeX     = 1.;
    this->gaussianSizeY     = 1.;
    this->gaussianSizeZ     = 1.;
}


SimplePeaksMoutainMapBuilder::Gaussian3DCurveBuilder * SimplePeaksMoutainMapBuilder::Gaussian3DCurveBuilder::setGaussianShiftX(float gShiftX)
{
    this->gaussianShiftX = gShiftX;

    return this;
}

SimplePeaksMoutainMapBuilder::Gaussian3DCurveBuilder * SimplePeaksMoutainMapBuilder::Gaussian3DCurveBuilder::setGaussianShiftY(float gShiftY)
{
    this->gaussianShiftY = gShiftY;

    return this;
}

SimplePeaksMoutainMapBuilder::Gaussian3DCurveBuilder * SimplePeaksMoutainMapBuilder::Gaussian3DCurveBuilder::setGaussianSizeX(float gSizeX)
{
    this->gaussianSizeX = gSizeX;

    return this;
}

SimplePeaksMoutainMapBuilder::Gaussian3DCurveBuilder * SimplePeaksMoutainMapBuilder::Gaussian3DCurveBuilder::setGaussianSizeY(float gSizeY)
{
    this->gaussianSizeY = gSizeY;

    return this;
}

SimplePeaksMoutainMapBuilder::Gaussian3DCurveBuilder * SimplePeaksMoutainMapBuilder::Gaussian3DCurveBuilder::setGaussianSizeZ(float gSizeZ)
{
    this->gaussianSizeZ = gSizeZ;

    return this;
}

SimplePeaksMoutainMapBuilder::Gaussian3DCurve * SimplePeaksMoutainMapBuilder::Gaussian3DCurveBuilder::make()
{
    return new SimplePeaksMoutainMapBuilder::Gaussian3DCurve(gaussianShiftX, gaussianShiftY, gaussianShiftX, gaussianShiftY, gaussianSizeZ);
}
