#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T23:51:52
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WorldXGen
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

LIBS += -lopengl32 -lglu32

SOURCES += main.cpp \
    mainwindow.cpp \
    glwidget.cpp \
    point3d.cpp \
    seed.cpp \
    map.cpp \
    mapbuilder.cpp \
    nouveaumondedialog.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    point3d.h \
    seed.h \
    map.h \
    mapbuilder.h \
    nouveaumondedialog.h

FORMS    += mainwindow.ui \
    nouveaumondedialog.ui
