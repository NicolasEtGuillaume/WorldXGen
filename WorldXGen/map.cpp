#include "map.h"

vector<Goutte *> Map::getGouttes() const
{
    return gouttes;
}

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
                pointA = this->getPoint((unsigned int) truncf(lastPoint->getX()),(unsigned int) truncf(lastPoint->getY()));
                cout << pointA->getZ() << endl;
            }else
            {
                pointA = this->getPoint((unsigned int) truncf(lastPoint->getX())+1,(unsigned int) truncf(lastPoint->getY())+1);
            }


            QVector3D * vecPointA = new QVector3D(pointA->getX(),pointA->getY(),pointA->getZ());
            QVector3D * vecPointB = new QVector3D(pointB->getX(),pointB->getY(),pointB->getZ());
            QVector3D * vecPointC = new QVector3D(pointC->getX(),pointC->getY(),pointC->getZ());

            // Calcul de la pente en 2 étapes
            // 1 - détermination d'une normale
            QVector3D * vecAB = new QVector3D(vecPointB->x()-vecPointA->x(),vecPointB->y()-vecPointA->y(),vecPointB->z()-vecPointA->z());
            QVector3D * vecAC = new QVector3D(vecPointC->x()-vecPointA->x(),vecPointC->y()-vecPointA->y(),vecPointC->z()-vecPointA->z());
            QVector3D * normale = new QVector3D(vecAB->y()*vecAC->z() - vecAC->y()*vecAB->z(),
                                                -(vecAB->x()*vecAC->z() - vecAC->x()*vecAB->z()),
                                                vecAB->x()*vecAC->y() - vecAC->x()*vecAB->y());

            // 2 - calcul du vecteur directeur de la ligne de plus grande pente
            // soit intersection entre le plan et celui formé par le vecteur normal et le projeté orthogonal
            // de ce dernier sur l'horizontale
            // vecteur normal (a,b,c)
            // projeté (a,b,0)
            // intersection : (ac,bc,a²+b²)
            QVector3D * pente = new QVector3D(normale->x()*normale->z(),
                                              normale->y()*normale->z(),
                                              normale->x()*normale->x() + normale->y()*normale->y());
            pente->normalize();


            // application sur le point (applyEuler() sur le point)
            curGoutte->applyEuler(*pente,pas,this->getSizeX(),this->getSizeY());


            //Projection sur le plan (recalcule de z)

            float ABz = pointB->getZ() - pointA->getZ();
            float ACz = pointC->getZ() - pointA->getZ();
            float uz = ABz * fabsf(lastPoint->getX() - pointA->getX());
            float vz = ACz * fabsf(lastPoint->getY() - pointA->getY());

            lastPoint->setZ(pointA->getZ() + uz + vz);
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

    // calcule de z

    float ABz = pointB->getZ() - pointA->getZ();
    float ACz = pointC->getZ() - pointA->getZ();
    float uz = ABz * fabsf(x - pointA->getX());
    float vz = ACz * fabsf(y - pointA->getY());

    z = pointA->getZ() + uz + vz;

    Goutte * goutte = new Goutte(x,y,z);
    this->gouttes.push_back(goutte);
}

unsigned int Map::getSizeX()
{
    return this->sizeX;
}

unsigned int Map::getSizeY()
{
    return this->sizeY;
}
