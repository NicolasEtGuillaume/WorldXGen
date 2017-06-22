#include "glwidget.h"

const float MAP_SIZE_LIMITER = 5.0;//Evite les problèmes d'affichages de trop grande map
GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    m_vertexbuffer(QGLBuffer::VertexBuffer),
    g_vertexbuffer(QGLBuffer::VertexBuffer)
{
    map = nullptr;
    filteredMap = nullptr;
}

GLWidget::~GLWidget()
{

}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(200,200);
}

QSize GLWidget::sizeHint() const
{
    return QSize(800,600);
}


void GLWidget::initializeGL()
{
    // View settings
    distance = -10.0;
    x_rot = 0;
    y_rot = 0;
    z_rot = 0;
    cameraAimX = 0.0;
    cameraAimY = 0.0;

    // GL options

    qglClearColor(Qt::darkGray);
    glEnable(GL_DEPTH_TEST);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, -distance, -distance,//TODO
              cameraAimX, cameraAimY, 0.0,
              0.0, 1.0, 0.0);

    glRotatef(x_rot / 16.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(y_rot / 16.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(z_rot / 16.0f, 0.0f, 0.0f, 1.0f);

    // Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f, 1.0*width()/height(), 0.1f, 100.0f);

    qglColor(Qt::white);
    // Method : Vertex Array
    glEnableClientState(GL_VERTEX_ARRAY);
    //glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, m_vertexarray.constData());
    glDrawArrays(GL_TRIANGLES, 0, m_vertexarray.size());


    qglColor(Qt::blue);
    //Affichage des gouttes
//    if(this->isMapSet()){
//        if(!map->getGouttes().empty()){
//            qglColor(Qt::blue);
//            for(int i = 0; i < g_vertexarray.size(); i++){
//                glVertexPointer(3, GL_FLOAT, 0, g_vertexarray[i].constData());
//                glDrawArrays(GL_LINES, 0, g_vertexarray[i].size());
//            }
//        }
//    }

    for ( QVector<QVector3D> river : g_vertexarray)
    {
        glVertexPointer(3, GL_FLOAT, 0, river.constData());
        glDrawArrays(GL_LINES, 0, river.size());
    }


    glDisableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_TEXTURE_COORD_ARRAY);



    //Affiche un repere
    glBegin(GL_LINES);
        qglColor(Qt::white);
        glVertex3f(0.0f, 0.0f, 0.0f);
        qglColor(Qt::red);
        glVertex3f(1.0f, 0.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
        qglColor(Qt::white);
        glVertex3f(0.0f, 0.0f, 0.0f);
        qglColor(Qt::blue);
        glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
        qglColor(Qt::white);
        glVertex3f(0.0f, 0.0f, 0.0f);
        qglColor(Qt::green);
        glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    last_pos = event->pos();
    updateGL();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{

    int dx = event->x() - last_pos.x();
    int dy = event->y() - last_pos.y();

    if (event->buttons() & Qt::RightButton)
    {
        rotateBy(dy*8, 0, 0);
        rotateBy(0, dx*8, 0);
    }
    if (event->buttons() & Qt::LeftButton)
    {
        this->setCursor(Qt::ClosedHandCursor);
        this->cameraAimX -= dx/32.0f;
        this->cameraAimY += dy/32.0f;
    }
    last_pos = event->pos();
    updateGL();

}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    distance *= 1.0 + (1.0 * event->delta() / 1200.0);
    updateGL();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    this->setCursor(Qt::ArrowCursor);
}

void GLWidget::rotateBy(int x, int y, int z)
{
    x_rot += x;
    y_rot += y;
    z_rot += z;
}

void GLWidget::setX_rot(const qreal &value)
{
    x_rot = value;
}

void GLWidget::setY_rot(const qreal &value)
{
    y_rot = value;
}

void GLWidget::setZ_rot(const qreal &value)
{
    z_rot = value;
}

void GLWidget::setCameraAimX(const GLdouble &value)
{
    cameraAimX = value;
}

void GLWidget::setCameraAimY(const GLdouble &value)
{
    cameraAimY = value;
}

Map * GLWidget::getMap() const
{
    return map;
}

void GLWidget::setMap(Map * value)
{
    this->map = value;
    filterMap();
}

bool GLWidget::isMapSet()
{
    return (this->map != nullptr);
}

Map * GLWidget::getFilteredMap() const
{
    return this->filteredMap;
}

void GLWidget::filterMap()
{
    this->filteredMap = this->map->clone();
    for (Filter * filter : this->filters) {
        this->filteredMap = filter->apply(this->filteredMap);
    }
}

void GLWidget::addMapFilter(FilterMatrix * filter)
{
    this->filters.push_back(filter);
}

void GLWidget::removeMapFilter(int filterIndex)
{
    this->filters.erase(this->filters.begin() + filterIndex);
}

void GLWidget::moveMapFilterUp(int filterIndex)
{
    if (filterIndex - 1 < 0) return;
    iter_swap(this->filters.begin() + filterIndex, this->filters.begin() + filterIndex - 1);
}

void GLWidget::moveMapFilterDown(int filterIndex)
{
    if (filterIndex + 1 == this->filters.size()) return;
    iter_swap(this->filters.begin() + filterIndex, this->filters.begin() + filterIndex + 1);
}

int GLWidget::getMapFiltersCount()
{
    return (int) this->filters.size();
}

FilterMatrix * GLWidget::getMapFilter(int filterIndex)
{
    return this->filters[filterIndex];
}

QString GLWidget::getMapFilterName(int filterIndex) {
    return this->filters[filterIndex]->customName;
}

void GLWidget::updateMapView()
{
    //modification des paramètre opengl pour afficher une map

    m_vertices.clear();
    m_vertexarray.clear();
    vertices_by_x = this->filteredMap->getSizeX();
    vertices_by_z = this->filteredMap->getSizeY();
    quads_by_x = vertices_by_x - 1;
    quads_by_z = vertices_by_z - 1;
    Point3D p = Point3D(0,0,0);
    QVector3D vertice;
    m_vertices.reserve(vertices_by_x * vertices_by_z);
    for(int z = 0; z < vertices_by_z; ++z)
    {
        for(int x = 0; x < vertices_by_x; ++x)
        {
                p = *(this->filteredMap->getPoint(x,z));
//                float norm = p.getX()*p.getX() + p.getY()*p.getY() +p.getZ()*p.getZ();
//                norm = sqrt(norm);
//                vertice.setX(MAP_SIZE * p.getX() / norm);
//                vertice.setY(MAP_SIZE * p.getZ() / norm);
//                vertice.setZ(MAP_SIZE * p.getY() / norm);
//                vertice.setX(x);
//                vertice.setY(p.getZ());
//                vertice.setZ(z);
//                vertice.normalize();

                vertice.setX((x/MAP_SIZE_LIMITER) - (vertices_by_x/MAP_SIZE_LIMITER/2));
                vertice.setY(p.getZ()/MAP_SIZE_LIMITER);
                vertice.setZ((z/MAP_SIZE_LIMITER) - (vertices_by_z/MAP_SIZE_LIMITER/2));

                m_vertices.push_back(vertice);
        }
    }


    m_vertexarray.reserve(quads_by_x * quads_by_z * 6);
    for (int z = 0; z < quads_by_z; ++z)
    {
        for (int x = 0; x < quads_by_x; ++x)
        {
            int i = z * vertices_by_x + x;

            // VertexArray
            m_vertexarray.push_back(m_vertices[i]);
            m_vertexarray.push_back(m_vertices[i+vertices_by_x]);
            m_vertexarray.push_back(m_vertices[i+1]);

            m_vertexarray.push_back(m_vertices[i+1]);
            m_vertexarray.push_back(m_vertices[i+vertices_by_x]);
            m_vertexarray.push_back(m_vertices[i+1+vertices_by_x]);
        }
    }

    // Vertex buffer init
    m_vertexbuffer.create();
    m_vertexbuffer.bind();
    m_vertexbuffer.allocate(m_vertices.constData(), m_vertices.size() * sizeof(QVector3D));
    m_vertexbuffer.release();

    g_vertexarray.clear();
    g_vertices.clear();
    g_vertexbuffer.create();
    g_vertexbuffer.bind();
    int verticesCount = 0;
    // ajout des gouttes
    if(!this->filteredMap->getGouttes().empty())
    {



        for(unsigned int i=0; i < this->filteredMap->getGouttes().size(); i++)
        {
            Goutte * curGoutte = this->filteredMap->getGouttes()[i];
            g_vertices.clear();

            g_vertices.reserve(curGoutte->getPoints().size());

            QVector<QVector3D> temp;

            for(unsigned int j=0; j < curGoutte->getPoints().size(); j++)
            {
                p = *curGoutte->getPoints()[j];

                vertice.setX((p.getX()/MAP_SIZE_LIMITER) - (vertices_by_x/MAP_SIZE_LIMITER/2));
                vertice.setY(p.getZ()/MAP_SIZE_LIMITER);
                vertice.setZ((p.getY()/MAP_SIZE_LIMITER) - (vertices_by_z/MAP_SIZE_LIMITER/2));

                g_vertices.push_back(vertice);
            }

            temp.reserve((g_vertices.size()-1)*2);
            for(int k=0; k < (g_vertices.size()-2); k++)
            {
                temp.push_back(g_vertices[k]);
                temp.push_back(g_vertices[k+1]);
            }

            g_vertexarray.push_back(temp);


            verticesCount += g_vertices.size();

        }

    }
    g_vertexbuffer.allocate(g_vertices.constData(),verticesCount * sizeof(QVector3D));
    g_vertexbuffer.release();

    this->setCursor(Qt::ArrowCursor);

    this->paintGL();
    this->updateGL();
}
