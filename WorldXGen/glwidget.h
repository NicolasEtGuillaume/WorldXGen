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
#include "filter.h"

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


    void addMapFilter(Filter * filter);
    void removeMapFilter(int filterIndex);
    void moveMapFilterUp(int filterIndex);
    void moveMapFilterDown(int filterIndex);
    int getMapFiltersCount();
    Filter * getMapFilter(int filterIndex);
    QString getMapFilterName(int filterIndex);

private:
    void rotateBy(int x, int y, int z);

    /**
     * Moves a range of values in a vector.
     * @param start     The range start position.
     * @param length    The range length.
     * @param dst       The range new start position.
     * @param v         The vector.
     *
     * @author Kerrek SB
     * @see https://stackoverflow.com/questions/7527674/what-is-the-most-effective-way-to-move-items-within-a-vector
     */
    void move_range(size_t start, size_t length, size_t dst, std::vector<Filter *> & v);

private:

    QVector<QVector3D> m_vertexarray;
    QVector<QVector3D> m_vertices;

    Map * map;
    vector<Filter *> filters;

    // GPU Buffer
    QGLBuffer m_vertexbuffer;

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
};

#endif // GLWIDGET_H
