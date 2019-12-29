#-------------------------------------------------
#
# Project created by QtCreator 2019-03-28T09:46:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = customgraphics
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcustomgraphics.cpp
SOURCES     += customgraphics.cpp

HEADERS     += frmcustomgraphics.h
HEADERS     += customgraphics.h

FORMS       += frmcustomgraphics.ui
