#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:17:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugeclock
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugeclock.cpp
SOURCES     += gaugeclock.cpp

HEADERS     += frmgaugeclock.h
HEADERS     += gaugeclock.h

FORMS       += frmgaugeclock.ui
