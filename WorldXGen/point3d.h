#ifndef POINT3D_H
#define POINT3D_H


class Point3D
{
private:
    float x;
    float y;
    float z;

public:

    /**
     * @brief Instantiates a Point3D object with its coordinates.
     * @param x The X coordinate of the point.
     * @param y The Y coordinate of the point.
     * @param z The Z coordinate of the point.
     */
    Point3D(float x, float y, float z);

    /**
     * @brief Gets the X coordinate of the point in its map.
     * @return The X coordinate.
     */
    float getX();

    /**
     * @brief Gets the Y coordinate of the point in its map.
     * @return The Y coordinate.
     */
    float getY();

    /**
     * @brief Gets the Z coordinate of the point in its map.
     * @return The Z coordinate.
     */
    float getZ();

    /**
     * @brief Sets the Z coordinate of the point.
     * @param The new Z coordinate.
     */
    void setZ(float z);
};

#endif // POINT3D_H
