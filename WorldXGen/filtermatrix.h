#ifndef FILTERMATRIX_H
#define FILTERMATRIX_H

#define DEFAULT_NAME    "Matrix"

#include <QString>
#include <valarray>
#include "filter.h"

using namespace std;

class FilterMatrix : public Filter
{
private:
    valarray<int> * matrix;

    /**
     * @brief Clamps a value between two boundaries.
     * @param left The lower bound.
     * @param value The value to clamp.
     * @param right The upper bound.
     * @return The clamped value.
     */
    int clamp(int left, int value, int right);

public:
    FilterMatrix(QString customName);
    FilterMatrix();

    /**
     * @brief Gets the filter's matrix.
     * @return The filter's matrix.
     */
    valarray<int> * getMatrix();

    /**
     * @brief Changes the filter's matrix.
     * @param matrix The new matrix.
     */
    void setMatrix(valarray<int> * matrix);

    /**
     * @brief Applies the filter to the given map.
     * @param map The map to use.
     * @return A copy of the given map with the filter applied.
     */
    Map * apply(Map * map);
};

#endif // FILTERMATRIX_H
