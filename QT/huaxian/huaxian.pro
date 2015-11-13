#-------------------------------------------------
#
# Project created by QtCreator 2015-10-29T22:15:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = huaxian
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QT += opengl

LIBS += -lglut -lGLU


SOURCES += main.cpp \
    glhuaxian.cpp

HEADERS += \
    glhuaxian.h
