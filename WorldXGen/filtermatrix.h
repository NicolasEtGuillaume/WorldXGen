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
    int clamp(int left, int value, int right);

public:
    FilterMatrix(QString customName);
    FilterMatrix();

    valarray<int> * getMatrix();
    void setMatrix(valarray<int> * matrix);

    Map * apply(Map * map);
};

#endif // FILTERMATRIX_H
