#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{

}



void GLWidget::initializeGL()
{
    glClearColor(1,1,0,1);
}

void GLWidget::paintGL()
{
    glClear((GL_COLOR_BUFFER_BIT));
}

void GLWidget::resizeGL(int w, int h)
{

}
