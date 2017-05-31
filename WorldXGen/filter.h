#ifndef FILTER_H
#define FILTER_H

#include "map.h"

class Filter
{
public:
    Filter();

    /**
     * @brief Applies the filter on the given map.
     * @param map The map that will go through the filter.
     * @return A new map with modifications applied.
     */
    virtual Map * apply(Map * map) = 0;
};

#endif // FILTER_H
