#ifndef CONICMOUNTAINMAPBUILDER_H
#define CONICMOUNTAINMAPBUILDER_H

#include <algorithm>
#include "random.h"
#include "mapbuilder.h"
#include "map.h"

class ConicMountainmapBuilder : public MapBuilder
{
public:
    Map * build();
};

#endif // CONICMOUNTAINMAPBUILDER_H
