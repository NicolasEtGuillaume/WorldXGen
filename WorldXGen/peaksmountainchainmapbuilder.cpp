#include "peaksmountainchainmapbuilder.h"

PeaksMountainChainMapBuilder::PeaksMountainChainMapBuilder()
{

}

Map * PeaksMountainChainMapBuilder::build()
{
    vector<Gaussian3DCurve *> curves;
    unsigned int seedValue = this->seed->getValue();
    unsigned int degree;
    srand(seedValue);

    std::mt19937 gen(seedValue);

    std::uniform_int_distribution<int> degreeRndDist(1, MAX_POLYNOMIAL);
    degree = degreeRndDist(gen);

    std::uniform_real_distribution<float> uniformD2(-2.f, 2.f);

    PolynomialFunctionBuilder * fb = new PolynomialFunctionBuilder();

    for (float curDegree = 0.f; curDegree < degree; ++curDegree)
    {
        float coefValue = uniformD2(gen);
        fb->addCoefficient(coefValue, curDegree);
    }

    PolynomialFunction * f = fb->build();

    std::uniform_int_distribution<int> uniformD3(RANDOM_CURVES_COUNT_MIN, RANDOM_CURVES_COUNT_MAX);
    float gaussianCurvesCount = uniformD3(gen);

    for (unsigned int i = 0; i < gaussianCurvesCount; ++i)
    {
        float gShiftX, gShiftY, gSizeX, gSizeY, gSizeZ, theta;

        std::uniform_real_distribution<float> d1(0.f, this->sizeX);
        gShiftX = d1(gen);

        float solved = f->solve(gShiftX);
        std::normal_distribution<float> d2(solved, 2.);
        gShiftY = d2(gen);

        std::normal_distribution<float> d3(this->sizeX / 8.f, 4.f);
        gSizeX = d3(gen);

        std::normal_distribution<float> d4(this->sizeY / 8.f, 4.f);
        gSizeY = d4(gen);

        std::normal_distribution<float> d5(this->sizeX * this->sizeY / 200.f, this->sizeX * this->sizeY / 400.f);
        gSizeZ = d5(gen);

        std::uniform_real_distribution<float> d6(0.f, (float) (2 * M_PI));
        theta = d6(gen);

        curves.push_back(new Gaussian3DCurve(gShiftX, gShiftY, gSizeX, gSizeY, gSizeZ, theta));
    }

    Map * generatedMap = new Map(this->sizeX, this->sizeY);

    vector<Point3D *> points = *(generatedMap->getAllPoints());

    for (Point3D * point : points)
    {
        bool firstOne = true;
        float finalZValue;

        for (Gaussian3DCurve * curve : curves)
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
