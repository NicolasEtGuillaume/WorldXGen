#ifndef FULLYRANDOMMAPBUILDER_H
#define FULLYRANDOMMAPBUILDER_H

#include "random.h"
#include "mapbuilder.h"
#include "map.h"

class FullyRandomMapBuilder : public MapBuilder
{
public:
    Map * build();
};

#endif // FULLYRANDOMMAPBUILDER_H
