#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:37:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugeprogress
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugeprogress.cpp
SOURCES     += gaugeprogress.cpp

HEADERS     += frmgaugeprogress.h
HEADERS     += gaugeprogress.h

FORMS       += frmgaugeprogress.ui
