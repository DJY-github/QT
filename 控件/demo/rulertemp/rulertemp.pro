#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:44:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = rulertemp
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmrulertemp.cpp
SOURCES     += rulertemp.cpp

HEADERS     += frmrulertemp.h
HEADERS     += rulertemp.h

FORMS       += frmrulertemp.ui
