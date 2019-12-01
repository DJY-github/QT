#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:08:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = rulerline
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmrulerline.cpp
SOURCES     += rulerline.cpp

HEADERS     += frmrulerline.h
HEADERS     += rulerline.h

FORMS       += frmrulerline.ui
