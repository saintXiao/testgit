#-------------------------------------------------
#
# Project created by QtCreator 2015-11-19T15:38:44
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = partical
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QT += opengl

LIBS += -lglut -lGLU \


SOURCES += main.cpp \
    vector3d.cpp \
    particalsystem.cpp \
    qwidget.cpp

HEADERS += \
    vector3d.h \
    particle.h \
    particalsystem.h \
    qwidget.h
