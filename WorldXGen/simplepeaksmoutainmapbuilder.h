#ifndef CONICMOUNTAINMAPBUILDER_H
#define CONICMOUNTAINMAPBUILDER_H

#include <algorithm>
#include <random>
#define _USE_MATH_DEFINES
#include <math.h>
#include "mapbuilder.h"
#include "gaussian3dcurve.h"
#include "map.h"

#define RANDOM_CURVES_COUNT_MIN 4
#define RANDOM_CURVES_COUNT_MAX 32
#define CURVE_HEIGHT_MAX        12

class SimplePeaksMoutainMapBuilder : public MapBuilder
{
public:

    SimplePeaksMoutainMapBuilder();

    /**
     * @brief Adds a gaussian curve.
     * @param curve The curve to add.
     * @return Itself, the same SimplePeaksMoutainMapBuilder instance (Factory pattern).
     */
    SimplePeaksMoutainMapBuilder * addGaussianCurve(Gaussian3DCurve * curve);

    /**
     * @brief Builds a map.
     * @return The built map.
     */
    Map * build();

    /**
     * @brief Builds a map.
     * @param randomCurves The generation will use random gaussian curves if True.
     * @return The built map.
     */
    Map * build(bool randomCurves);

private:
    vector<Gaussian3DCurve *> curves;
};

#endif // CONICMOUNTAINMAPBUILDER_H
