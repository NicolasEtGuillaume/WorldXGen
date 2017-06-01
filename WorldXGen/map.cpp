#include "map.h"

Map::Map(unsigned int sizeX, unsigned int sizeY)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    Point3D * pompote;
    for (unsigned int x = 0; x < sizeX; ++x)
    {
        for (unsigned int y = 0; y < sizeY; ++y)
        {
            pompote = new Point3D((float) x, (float) y, (float) 0);
            this->points.push_back(pompote);
        }
    }
}

Point3D * Map::getPoint(unsigned int x, unsigned int y)
{
    Point3D * foundPoint = nullptr;

    for (unsigned int i = 0; i < this->points.size() && foundPoint == nullptr; ++i)
    {
        Point3D * curPoint = this->points[i];

        if (curPoint->getX() == x && curPoint->getY() == y)
        {
            foundPoint = curPoint;
            // The loop will end when this variable will
            // get a different value than nullptr.
        }
    }

    return foundPoint;
}

vector<Point3D *> * Map::getAllPoints()
{
    return &(this->points);
}

string Map::getName()
{
    return this->name;
}

bool Map::iterationEuler(float pas)
{
    // Parcours les gouttes
        // Si la rivière n'est pas fini (bool end)
            // Repère la position de la goutte sur la map
            // Calcul du gradient
            // application sur le point (applyEuler() sur le point)

    // Si aucune goutte n'a été traitée (ce sont toutes de rivières) renvois false sinon true
    return false;
}

void Map::addGoutte(float x, float y)
{
    float z =0;
    // Repère la position de la goutte sur la map
    // calcul de z
    gouttes.push_back(new Goutte(x,y,z));
}

unsigned int Map::getSizeX()
{
    return this->sizeX;
}

unsigned int Map::getSizeY()
{
    return this->sizeY;
}
