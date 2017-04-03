#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T23:51:52
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WorldXGen
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    point3d.cpp \
    seed.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    point3d.h \
    seed.h

FORMS    += mainwindow.ui
