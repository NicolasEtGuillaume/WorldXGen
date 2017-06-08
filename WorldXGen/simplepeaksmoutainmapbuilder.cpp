#include "simplepeaksmoutainmapbuilder.h"

SimplePeaksMoutainMapBuilder::SimplePeaksMoutainMapBuilder()
{

}

SimplePeaksMoutainMapBuilder * SimplePeaksMoutainMapBuilder::addGaussianCurve(SimplePeaksMoutainMapBuilder::Gaussian3DCurve * curve)
{
    this->curves.push_back(curve);

    return this;
}

Map * SimplePeaksMoutainMapBuilder::build(bool randomCurves)
{
    unsigned int seedValue = this->seed->getValue();
    srand(seedValue);

    std::mt19937 gen(seedValue);

    if (randomCurves)
    {

        float gaussianCurvesCount = Random::uniformDistribution(RANDOM_CURVES_COUNT_MIN, RANDOM_CURVES_COUNT_MAX);;



        for (unsigned int i = 0; i < gaussianCurvesCount; ++i)
        {
            float gShiftX, gShiftY, gSizeX, gSizeY, gSizeZ, theta;

            std::uniform_real_distribution<float> d1(0.f, this->sizeX);
            gShiftX = d1(gen);

            std::uniform_real_distribution<float> d2(0.f, this->sizeY);
            gShiftY = d2(gen);

            std::normal_distribution<float> d3(this->sizeX / 8.f, 4.f);
            gSizeX = d3(gen);

            std::normal_distribution<float> d4(this->sizeY / 8.f, 4.f);
            gSizeY = d4(gen);

            std::normal_distribution<float> d5(this->sizeX * this->sizeY / 200.f, this->sizeX * this->sizeY / 400.f);
            gSizeZ = d5(gen);

            std::uniform_real_distribution<float> d6(0.f, (float) (2 * M_PI));
            theta = d6(gen);

            addGaussianCurve(new Gaussian3DCurve(gShiftX, gShiftY, gSizeX, gSizeY, gSizeZ, theta));
        }
    }

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

Map * SimplePeaksMoutainMapBuilder::build()
{
    return SimplePeaksMoutainMapBuilder::build(true);
}

/*
 * Gaussian3DCurve
 */

SimplePeaksMoutainMapBuilder::Gaussian3DCurve::Gaussian3DCurve(float gShiftX, float gShiftY, float gSizeX, float gSizeY, float gSizeZ, float gTheta)
{
    this->gaussianShiftX    = gShiftX;
    this->gaussianShiftY    = gShiftY;
    this->gaussianSizeX     = gSizeX;
    this->gaussianSizeY     = gSizeY;
    this->gaussianSizeZ     = gSizeZ;
    this->theta             = gTheta;
}

float SimplePeaksMoutainMapBuilder::Gaussian3DCurve::getValue(float x, float y)
{

    float   a = powf(cosf(this->theta), 2.f) / (2 * powf(this->gaussianSizeX, 2.f)) + powf(sinf(this->theta), 2.f) / (2 * powf(this->gaussianSizeY, 2.f)),
            b = -sinf(2 * this->theta) / (4 * powf(this->gaussianSizeX, 2.f)) + sinf(2 * this->theta) / (4 * powf(this->gaussianSizeY, 2.f)),
            c = powf(sinf(this->theta), 2.f) / (2 * powf(this->gaussianSizeX, 2.f)) + powf(cosf(this->theta), 2.f) / (2 * powf(this->gaussianSizeY, 2.f));


    return exp(
        -(a * powf(x - this->gaussianShiftX, 2.f) + 2 * b * (x - this->gaussianShiftX) * (y - this->gaussianShiftY) + c * powf(y - this->gaussianShiftY, 2.f))
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

SimplePeaksMoutainMapBuilder::Gaussian3DCurveBuilder * SimplePeaksMoutainMapBuilder::Gaussian3DCurveBuilder::setTheta(float gTheta)
{
    this->theta = gTheta;

    return this;
}

SimplePeaksMoutainMapBuilder::Gaussian3DCurve * SimplePeaksMoutainMapBuilder::Gaussian3DCurveBuilder::make()
{
    return new SimplePeaksMoutainMapBuilder::Gaussian3DCurve(gaussianShiftX, gaussianShiftY, gaussianShiftX, gaussianShiftY, gaussianSizeZ, theta);
}
