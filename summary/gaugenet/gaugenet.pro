#-------------------------------------------------
#
# Project created by QtCreator 2016-12-16T16:18:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugenet
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off
RESOURCES   += main.qrc

SOURCES     += main.cpp
SOURCES     += frmgaugenet.cpp
SOURCES     += gaugenet.cpp

HEADERS     += frmgaugenet.h
HEADERS     += gaugenet.h

FORMS       += frmgaugenet.ui
