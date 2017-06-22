#ifndef GOUTTE_H
#define GOUTTE_H

#include <string>
#include <vector>
#include "point3d.h"
#include <QVector3D>
#include <iostream>

using namespace std;

class Goutte
{
private:
    vector<Point3D *> points;
    bool end;

public:
    Goutte(float x, float y, float z);

    /**
     * @brief Gets the last point computed with the Euler algorithm.
     * @return The last point computed with the Euler algorithm.
     */
    Point3D * getLastPoint();

    void applyEuler(QVector3D gradient, float pas, unsigned int mapSizeX, unsigned int mapSizeY);
    bool getEnd() const;
    vector<Point3D *> getPoints() const;
};

#endif // GOUTTE_H
