#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:09:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = roundcircle
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmroundcircle.cpp
SOURCES     += roundcircle.cpp

HEADERS     += frmroundcircle.h
HEADERS     += roundcircle.h

FORMS       += frmroundcircle.ui
