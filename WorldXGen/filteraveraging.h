#ifndef FILTERAVERAGING_H
#define FILTERAVERAGING_H

#include <algorithm>
#include "point3d.h"
#include "map.h"
#include "filter.h"

class FilterAveraging : public Filter
{
public:
    FilterAveraging();

    /**
     * @brief Applies the averaging filter on the given map.
     * @param map The map that will go through the averaging filter.
     * @return A new map with modifications applied.
     */
    Map * apply(Map * map);
};

#endif // FILTERAVERAGING_H
