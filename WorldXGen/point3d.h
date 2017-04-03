#ifndef POINT3D_H
#define POINT3D_H


class Point3D
{
private:
    float x;
    float y;
    float z;

public:
    Point3D(float x, float y, float z);

    float getX();
    float getY();
    float getZ();

    void setZ(float z);
};

#endif // POINT3D_H
