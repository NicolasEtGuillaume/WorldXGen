#include "map.h"

Map::Map(unsigned int sizeX, unsigned int sizeY)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    Point3D * pompote;
    for (unsigned int x = 0; x < sizeX; ++x)
    {
        for (unsigned int y = 0; y < sizeY; ++y)
        {
            pompote = new Point3D((float) x, (float) y, (float) 0);
            this->points.push_back(pompote);
        }
    }
}

Point3D * Map::getPoint(unsigned int x, unsigned int y)
{
    Point3D * foundPoint = nullptr;

    for (unsigned int i = 0; i < this->points.size() && foundPoint == nullptr; ++i)
    {
        Point3D * curPoint = this->points[i];

        if (curPoint->getX() == x && curPoint->getY() == y)
        {
            foundPoint = curPoint;
            // The loop will end when this variable will
            // get a different value than nullptr.
        }
    }

    return foundPoint;
}

vector<Point3D *> * Map::getAllPoints()
{
    return &(this->points);
}

string Map::getName()
{
    return this->name;
}

bool Map::iterationEuler(float pas)
{
    bool treated = false;
    // Parcours les gouttes
    for(unsigned int i =0; i < this->gouttes.size(); i++)
    {
        Goutte * curGoutte = this->gouttes[i];
        // Si la rivière n'est pas fini (bool end)
        if(!curGoutte->getEnd())
        {
            treated = true;

            // Repère la position du dernier point de la riviere sur la map
            // a b  ou    b
            // c        c a
            Point3D * lastPoint = curGoutte->getLastPoint();
            Point3D *pointB = this->getPoint((unsigned int) truncf(lastPoint->getX())+1,(unsigned int) truncf(lastPoint->getY()));
            Point3D *pointC = this->getPoint((unsigned int) truncf(lastPoint->getX()),(unsigned int) truncf(lastPoint->getY())+1);
            // Quelle point a prendre ?
            Point3D *pointA;
            if((lastPoint->getX() - truncf(lastPoint->getX()) + lastPoint->getY() - truncf(lastPoint->getY())) <= 1)
            {
                Point3D *pointA = this->getPoint((unsigned int) truncf(lastPoint->getX()),(unsigned int) truncf(lastPoint->getY()));
            }else
            {
                Point3D *pointA = this->getPoint((unsigned int) truncf(lastPoint->getX())+1,(unsigned int) truncf(lastPoint->getY())+1);
            }

            // Calcul du gradient

            // application sur le point (applyEuler() sur le point)



            //Projection sur le plan
            QVector3D * vecGoutte = new QVector3D(lastPoint->getX(),lastPoint->getY(),0);
            QVector3D * vecPointA = new QVector3D(pointA->getX(),pointA->getY(),pointA->getZ());
            QVector3D * vecPointB = new QVector3D(pointB->getX(),pointB->getY(),pointB->getZ());
            QVector3D * vecPointC = new QVector3D(pointC->getX(),pointC->getY(),pointC->getZ());
            lastPoint->setZ(- vecGoutte->distanceToPlane(*vecPointA,*vecPointB,*vecPointC));
        }
    }

    // Si aucune goutte n'a été traitée (ce sont toutes de rivières) renvois false sinon true
    return treated;
}

void Map::addGoutte(float x, float y)
{
    float z =0;
    // Repère la position de la goutte sur la map
    Point3D *pointB = this->getPoint((unsigned int) truncf(x)+1,(unsigned int) truncf(y));
    Point3D *pointC = this->getPoint((unsigned int) truncf(x),(unsigned int) truncf(y)+1);
    // Quelle point a prendre ?
    Point3D *pointA;
    if((x - truncf(x) + y - truncf(y)) <= 1)
    {
        pointA = this->getPoint((unsigned int) truncf(x),(unsigned int) truncf(y));
    }else
    {
        pointA = this->getPoint((unsigned int) truncf(x)+1,(unsigned int) truncf(y)+1);
    }

    // calcul de z
    QVector3D * goutte = new QVector3D(x,y,z);
    QVector3D * vecPointA = new QVector3D(pointA->getX(),pointA->getY(),pointA->getZ());
    QVector3D * vecPointB = new QVector3D(pointB->getX(),pointB->getY(),pointB->getZ());
    QVector3D * vecPointC = new QVector3D(pointC->getX(),pointC->getY(),pointC->getZ());
    z = - goutte->distanceToPlane(*vecPointA,*vecPointB,*vecPointC);



    gouttes.push_back(new Goutte(x,y,z));
}

unsigned int Map::getSizeX()
{
    return this->sizeX;
}

unsigned int Map::getSizeY()
{
    return this->sizeY;
}
