#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include "map.h"

class MapBuilder
{
protected:
    unsigned int sizeX;
    unsigned int sizeY;
public:
    /**
     * @brief Instantiates a MapBuilder object without any default size.
     */
    MapBuilder();

    /**
     * @brief Instantiates a MapBuilder object with a default map size.
     * @param sizeX The map's X size.
     * @param sizeY The map's Y size.
     */
    MapBuilder(unsigned int sizeX, unsigned int sizeY);

    /**
     * @brief Sets the map's size in the X axis.
     * @param sizeX The map's X size.
     * @return Itself, the same MapBuilder instance (Factory pattern).
     */
    MapBuilder * setSizeX(unsigned int sizeX);

    /**
     * @brief Sets the map's size in the Y axis.
     * @param sizeY The map's Y size.
     * @return Itself, the same MapBuilder instance (Factory pattern).
     */
    MapBuilder * setSizeY(unsigned int sizeY);

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
    virtual Map * build() const = 0;
};

#endif // MAPBUILDER_H
