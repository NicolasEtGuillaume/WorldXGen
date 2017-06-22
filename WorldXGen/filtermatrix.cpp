#include "filtermatrix.h"

FilterMatrix::FilterMatrix(QString customName)
{
    this->customName = customName;
}

FilterMatrix::FilterMatrix()
{
    this->customName = DEFAULT_NAME;
}

valarray<int> * FilterMatrix::getMatrix()
{
    return this->matrix;
}

void FilterMatrix::setMatrix(valarray<int> * matrix)
{
    this->matrix = matrix;
}

Map * FilterMatrix::apply(Map * map)
{
    unsigned int mapSizeX = map->getSizeX();
    unsigned int mapSizeY = map->getSizeY();
    Map * newMap = new Map(map->getSizeX(), map->getSizeY());

    // For each old point in the input map.
    for (unsigned int x = 0; x < mapSizeX; ++x)
    {
        for (unsigned int y = 0; y < mapSizeY; ++y)
        {
            float newZ = 0;
            int coefSum = 0;

            // for each coefficient in the matrix.
            for (int i = 0; i < 25; ++i)
            {
                int mX = i % 5;
                int mY = i / 5;
                int coef = (*(this->matrix))[i];

                if(coef == 0) continue;

                Point3D * point = map->getPoint(
                    clamp(0, x - 2 + mX, mapSizeX - 1),
                    clamp(0, y - 2 + mY, mapSizeY - 1)
                );

                newZ += point->getZ() * coef;
                coefSum += coef;
            }

            if (coefSum != 0)
            {
                newZ /= coefSum;
            }
            newMap->getPoint(x, y)->setZ(newZ);
        }
    }

    return newMap;
}

int FilterMatrix::clamp(int left, int value, int right) {
    return min(max(left, value), right);
}
