#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include "map.h"

class MapBuilder
{
public:
    MapBuilder();

    /**
     * @brief Sets the seed of a map.
     * @param seed The seed to use.
     * @return Itself, the same MapBuilder instance (Factory pattern).
     */
    MapBuilder * setSeed(string seed);

    /**
     * @brief Applies erosion on the map.
     * @param level The level of erosion.
     * @return Itself, the same MapBuilder instance (Factory pattern).
     */
    MapBuilder * applyErosion(float level);

    /**
     * @brief Generates the map according to the given parameters.
     * @return The generated Map instance.
     */
    Map * build();
};

#endif // MAPBUILDER_H
