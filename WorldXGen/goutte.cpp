#include "goutte.h"

Goutte::Goutte(float x, float y, float z)
{
    Point3D * p;
    p = new Point3D(x,y,z);
    this->points.push_back(p);
    end = false;
}

Point3D *Goutte::getLastPoint()
{
    return this->points.back();
}

void Goutte::applyEuler(QVector3D gradient, float pas)
{
    //applique Euler sur la goutte
    //ajoutte un point en direction du gradient à pas plus loin
    //Projection sur le plan

    // Si on a pas assez bougé, end = true;
}
