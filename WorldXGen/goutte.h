#ifndef GOUTTE_H
#define GOUTTE_H

#include <string>
#include <vector>
#include "point3d.h"
#include <QVector3D>

using namespace std;

class Goutte
{
private:
    vector<Point3D *> points;
    bool end;

public:
    Goutte(float x, float y, float z);

    Point3D * getLastPoint();
    void applyEuler(QVector3D gradient, float pas);
};

#endif // GOUTTE_H
