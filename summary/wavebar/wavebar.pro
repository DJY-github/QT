#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:42:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = wavebar
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmwavebar.cpp
SOURCES     += wavebar.cpp

HEADERS     += frmwavebar.h
HEADERS     += wavebar.h

FORMS       += frmwavebar.ui
