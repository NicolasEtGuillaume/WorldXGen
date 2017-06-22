#ifndef FULLYRANDOMMAPBUILDER_H
#define FULLYRANDOMMAPBUILDER_H

#include "random.h"
#include "mapbuilder.h"
#include "map.h"

class FullyRandomMapBuilder : public MapBuilder
{
public:
    /**
     * @brief Builds a map.
     * @return A map instance.
     */
    Map * build();
};

#endif // FULLYRANDOMMAPBUILDER_H
