#include "point3d.h"

Point3D::Point3D(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

float Point3D::getX()
{
    return this->x;
}

float Point3D::getY()
{
    return this->y;
}

float Point3D::getZ()
{
    return this->z;
}

void Point3D::setZ(float z)
{
    this->z = z;
}
