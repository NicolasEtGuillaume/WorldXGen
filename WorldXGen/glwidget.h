#ifndef GLWIDGET_H
#define GLWIDGET_H


#include <QtGui/qopengl.h>
#include <QtGui>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLBuffer>
#include <gl/GLU.h>
#include "mapbuilder.h"
#include "map.h"
#include <iostream>
class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);



    void updateMapView();

    Map * getMap() const;
    void setMap(Map * value);

private:
    void rotateBy(int x, int y, int z);

private:

    QVector<QVector3D> m_vertexarray;
    QVector<QVector3D> m_vertices;

    QVector<QVector3D> g_vertexarray;
    QVector<QVector3D> g_vertices;

    Map * map;

    // GPU Buffer
    QGLBuffer m_vertexbuffer;
    QGLBuffer g_vertexbuffer;

    // Heightmap infos
    int vertices_by_x;
    int vertices_by_z;
    int quads_by_x;
    int quads_by_z;

    // View settings
    QPoint last_pos;
    float distance;
    qreal x_rot;
    qreal y_rot;
    qreal z_rot;
    GLdouble cameraAimX;
    GLdouble cameraAimY;
    GLdouble cameraAimZ;
};

#endif // GLWIDGET_H
