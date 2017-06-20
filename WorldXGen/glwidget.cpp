#include "glwidget.h"

const float MAP_SIZE_LIMITER = 5.0;//Evite les problèmes d'affichages de trop grande map
GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent),
    m_vertexbuffer(QGLBuffer::VertexBuffer)
{

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
    cameraAimZ = 0.0;

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
    gluLookAt(cameraAimX, 0.0, -distance+cameraAimY,//TODO
              cameraAimX, 0.0, cameraAimY,
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


    //Affichage des gouttes
    qglColor(Qt::cyan);
    glVertexPointer(3, GL_FLOAT, 0, g_vertexarray.constData());
    glDrawArrays(GL_LINES, 0, g_vertexarray.size());

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
        this->cameraAimX -= dx/8.0f;
        this->cameraAimY += dy/8.0f;
    }
    last_pos = event->pos();
    updateGL();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    distance *= 1.0 + (1.0 * event->delta() / 1200.0);
    updateGL();
}

void GLWidget::rotateBy(int x, int y, int z)
{
    x_rot += x;
    y_rot += y;
    z_rot += z;
}

Map * GLWidget::getMap() const
{
    return map;
}

void GLWidget::setMap(Map * value)
{
    map = value;
}


void GLWidget::updateMapView()
{
    //modification des paramètre opengl pour afficher une map


    m_vertices.clear();
    m_vertexarray.clear();
    vertices_by_x = map->getSizeX();
    vertices_by_z = map->getSizeY();
    quads_by_x = vertices_by_x - 1;
    quads_by_z = vertices_by_z - 1;
    Point3D p = Point3D(0,0,0);
    QVector3D vertice;
    m_vertices.reserve(vertices_by_x * vertices_by_z);
    for(int z = 0; z < vertices_by_z; ++z)
    {
        for(int x = 0; x < vertices_by_x; ++x)
        {
                p = *map->getPoint(x,z);
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

    // ajout des gouttes
    if(!map->getGouttes().empty())
    {

        g_vertices.clear();
        g_vertexarray.clear();
        g_vertices.reserve(map->getGouttes()[0]->getPoints().size());
        for(unsigned int i=0; i < map->getGouttes().size(); i++)
        {
            Goutte * curGoutte = map->getGouttes()[i];

            for(unsigned int j=0; j < curGoutte->getPoints().size(); j++)
            {
                p = *curGoutte->getPoints()[j];
                cout << "l : " << p.getX() << " " << p.getY() << endl;

                vertice.setX((p.getX()/MAP_SIZE_LIMITER) - (vertices_by_x/MAP_SIZE_LIMITER/2));
                vertice.setY(p.getZ()/MAP_SIZE_LIMITER);
                vertice.setZ((p.getY()/MAP_SIZE_LIMITER) - (vertices_by_z/MAP_SIZE_LIMITER/2));

                g_vertices.push_back(vertice);
            }
        }
        g_vertexarray.reserve((g_vertices.size()-1)*2);
        for(int i=0; i < (g_vertices.size()-2); i++)
        {
            g_vertexarray.push_back(g_vertices[i]);
            g_vertexarray.push_back(g_vertices[i+1]);
        }

        g_vertexbuffer.create();
        g_vertexbuffer.bind();
        g_vertexbuffer.allocate(g_vertices.constData(),g_vertices.size() * sizeof(QVector3D));
        g_vertexbuffer.release();
    }



    this->paintGL();
}
