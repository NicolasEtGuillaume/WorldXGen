/**
 * @file map.h
 * @brief Map class, used to store information about the map.
 */

#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include "point3d.h"
#include <iostream>
#include "goutte.h"
#include <math.h>

using namespace std;

class Map
{
private:
    vector<Point3D *> points;
    vector<Goutte *> gouttes;
    string name;
    unsigned int sizeX;
    unsigned int sizeY;

public:

    /**
     * @brief Instantiates a Map object with its size, each point will get instantiated too.
     * @param sizeX The map's X size.
     * @param sizeY The map's Y size.
     */
    Map(unsigned int sizeX, unsigned int sizeY);

    /**
     * @brief Gets the point associated with the given coordinates.
     * @param x The point's X coordinate.
     * @param y The point's Y coordinate.
     * @return The asked point if found, nullptr otherwise.
     */
    Point3D * getPoint(unsigned int x, unsigned int y);

    /**
     * @brief Gets a vector containing all points.
     * @return All points in a dynamic vector.
     */
    vector<Point3D *> * getAllPoints();

    /**
     * @brief Gets the name string associated with the map.
     * @return The name of the map.
     */
    string getName();


    bool iterationEuler(float pas);

    void addGoutte(float x, float y);

    /**
     * @brief Gets the map's X size.
     * @return The map's X size.
     */
    unsigned int getSizeX();

    /**
     * @brief Gets the map's Y size.
     * @return The map's Y size.
     */
    unsigned int getSizeY();

    /**
     * @brief Gets the water drops associated with the map.
     * @return The water drop instances.
     */
    vector<Goutte *> getGouttes() const;

    /**
     * @brief Clones the current map, copies every point.
     * @return A new map, the same as the used one.
     */
    Map * clone();
};

#endif // MAP_H
