#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:24:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = rulerslider
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmrulerslider.cpp
SOURCES     += rulerslider.cpp

HEADERS     += frmrulerslider.h
HEADERS     += rulerslider.h

FORMS       += frmrulerslider.ui
