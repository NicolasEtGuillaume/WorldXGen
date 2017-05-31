#include "mapbuilder.h"

MapBuilder::MapBuilder(unsigned int sizeX, unsigned int sizeY)
{
    this->setSizeX(sizeX)->setSizeY(sizeY);
}

MapBuilder::MapBuilder()
{

}

MapBuilder * MapBuilder::setSizeX(unsigned int sizeX)
{
    this->sizeX = sizeX;
    return this;
}

MapBuilder * MapBuilder::setSizeY(unsigned int sizeY)
{
    this->sizeY = sizeY;
    return this;
}

MapBuilder * MapBuilder::setSeed(string seed)
{
    this->seed = new Seed(seed);
    return this;
}

MapBuilder * MapBuilder::setSeed(Seed * seed)
{
    this->seed = seed;
    return this;
}

Map * MapBuilder::build()
{
    return nullptr;
}
