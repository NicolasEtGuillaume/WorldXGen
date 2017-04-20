#include "mapbuilder.h"

MapBuilder::MapBuilder()
{

}

MapBuilder * MapBuilder::setSeed(string seed)
{
    return this;
}

MapBuilder * MapBuilder::applyErosion(float level)
{
    return this;
}

Map * MapBuilder::build()
{
    return nullptr;
}
