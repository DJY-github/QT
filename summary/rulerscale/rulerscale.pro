#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:32:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = rulerscale
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmrulerscale.cpp
SOURCES     += rulerscale.cpp

HEADERS     += frmrulerscale.h
HEADERS     += rulerscale.h

FORMS       += frmrulerscale.ui
