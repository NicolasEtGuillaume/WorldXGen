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
    float epsilon = 0.01f;


    //applique Euler sur la goutte
    //ajoutte un point en direction du gradient à pas plus loin
    Point3D * lastPoint = this->getLastPoint();
    Point3D * p = new Point3D(lastPoint->getX() + gradient.x()*pas,
                              lastPoint->getY() + gradient.y()*pas,
                              lastPoint->getZ() + gradient.z()*pas);
    Point3D * p9;

    // Si on a pas assez bougé ou que l'on est sorti de la map, la rivière est fini sinon on push
    if(this->getPoints().size() > 50){
        p9 = this->getPoints()[this->getPoints().size() - 50];
        if((
                    (fabsf(p9->getX() - p->getX()) <= epsilon)
                    && (fabsf(p9->getY() - p->getY()) <= epsilon))
            ||
            (p->getX() > mapSizeX-1 || p->getY() > mapSizeY-1 || p->getX() < 0 || p->getY() < 0))
        {
            this->end = true;
        }else{
            this->points.push_back(p);
        }
    }else{
        if(p->getX() > mapSizeX-1 || p->getY() > mapSizeY-1 || p->getX() < 0 || p->getY() < 0)
        {
            this->end = true;
        }else{
            this->points.push_back(p);
        }
    }

}
