#include "simplepeaksmoutainmapbuilder.h"

SimplePeaksMoutainMapBuilder::SimplePeaksMoutainMapBuilder()
{

}

SimplePeaksMoutainMapBuilder * SimplePeaksMoutainMapBuilder::addGaussianCurve(Gaussian3DCurve * curve)
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

        float gaussianCurvesCount = Random::uniformDistribution(RANDOM_CURVES_COUNT_MIN, RANDOM_CURVES_COUNT_MAX);



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

        for (Gaussian3DCurve * curve : this->curves)
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
