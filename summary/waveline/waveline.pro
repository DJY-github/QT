#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:46:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = waveline
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmwaveline.cpp
SOURCES     += waveline.cpp

HEADERS     += frmwaveline.h
HEADERS     += waveline.h

FORMS       += frmwaveline.ui
