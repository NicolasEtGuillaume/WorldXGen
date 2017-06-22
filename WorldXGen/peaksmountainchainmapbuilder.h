#ifndef PEAKSMOUNTAINCHAINMAPBUILDER_H
#define PEAKSMOUNTAINCHAINMAPBUILDER_H

#include <random>
#define _USE_MATH_DEFINES
#include <math.h>
#include "map.h"
#include "mapbuilder.h"
#include "gaussian3dcurve.h"
#include "polynomialfunction.h"

#define MAX_POLYNOMIAL 3
#define RANDOM_CURVES_COUNT_MIN 4
#define RANDOM_CURVES_COUNT_MAX 32

class PeaksMountainChainMapBuilder : public MapBuilder
{
public:
    PeaksMountainChainMapBuilder();

    /**
     * @brief Builds a map.
     * @return The built map.
     */
    Map * build();
};

#endif // PEAKSMOUNTAINCHAINMAPBUILDER_H
