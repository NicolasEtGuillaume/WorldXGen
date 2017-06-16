#include "goutte.h"

bool Goutte::getEnd() const
{
    return end;
}

vector<Point3D *> Goutte::getPoints() const
{
    return points;
}

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

void Goutte::applyEuler(QVector3D gradient, float pas, unsigned int mapSizeX, unsigned int mapSizeY)
{
    float epsilon = 0.001f;

    //applique Euler sur la goutte
    //ajoutte un point en direction du gradient à pas plus loin
    Point3D * lastPoint = this->getLastPoint();
    Point3D * p = new Point3D(lastPoint->getX() + gradient.x()*pas,
                              lastPoint->getY() + gradient.y()*pas,
                              lastPoint->getZ() + gradient.z()*pas);

    // Si on a pas assez bougé ou que l'on est sorti de la map, la rivière est fini sinon on push
    if(((lastPoint->getX()-p->getX() < epsilon) && (lastPoint->getY()-p->getY() < epsilon))
        ||
        (p->getX() > mapSizeX-1 || p->getY() > mapSizeY-1))
    {
        this->end = true;
    }else{
        this->points.push_back(p);
    }
}
