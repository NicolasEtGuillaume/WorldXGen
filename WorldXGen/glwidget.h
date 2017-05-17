#ifndef GLWIDGET_H
#define GLWIDGET_H


#include <QtGui/qopengl.h>
#include <QtGui>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <gl/GLU.h>
#include "mapbuilder.h"

class GLWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);


    MapBuilder getMapBuilder() const;
    void setMapBuilder(const MapBuilder &value);

    void updateMapView();

private:
    void rotateBy(int x, int y, int z);

private:

    MapBuilder mapBuilder;

    // View settings
    QPoint last_pos;
    float distance;
    qreal x_rot;
    qreal y_rot;
    qreal z_rot;
};

#endif // GLWIDGET_H
