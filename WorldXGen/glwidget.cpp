#include "glwidget.h"

const float MAP_SIZE = 5.0;
GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{

}

GLWidget::~GLWidget()
{

}



void GLWidget::initializeGL()
{
    // View settings
    distance = -10.0;
    x_rot = 0;
    y_rot = 0;
    z_rot = 0;

    // GL options

    glClearColor(0.2f,0.2f,0.2f,0.0f);
    glEnable(GL_DEPTH_TEST);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, -distance,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glRotatef(x_rot / 16.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(y_rot / 16.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(z_rot / 16.0f, 0.0f, 0.0f, 1.0f);

    // Projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f, 1.0*width()/height(), 0.1f, 100.0f);

    // Method : Vertex Array
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, m_vertexarray.constData());

    glDrawArrays(GL_TRIANGLES, 0, m_vertexarray.size());

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    last_pos = event->pos();
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
    last_pos = event->pos();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    distance *= 1.0 + (1.0 * event->delta() / 1200.0);
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
                vertice.setX((MAP_SIZE * p.getX() / vertices_by_x) - MAP_SIZE / 2);
                vertice.setY((MAP_SIZE * p.getZ() / vertices_by_z) - MAP_SIZE / 2);
                vertice.setZ((MAP_SIZE * p.getY() / vertices_by_z) - MAP_SIZE / 2);
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
}
