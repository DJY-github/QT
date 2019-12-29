#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:32:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = rulerbar
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmrulerbar.cpp
SOURCES     += rulerbar.cpp

HEADERS     += frmrulerbar.h
HEADERS     += rulerbar.h

FORMS       += frmrulerbar.ui
