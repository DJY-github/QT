#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:54:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = xprogressbar
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmxprogressbar.cpp
SOURCES     += xprogressbar.cpp

HEADERS     += frmxprogressbar.h
HEADERS     += xprogressbar.h

FORMS       += frmxprogressbar.ui
