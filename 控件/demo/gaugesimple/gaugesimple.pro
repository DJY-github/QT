#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:55:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugesimple
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugesimple.cpp
SOURCES     += gaugesimple.cpp

HEADERS     += frmgaugesimple.h
HEADERS     += gaugesimple.h

FORMS       += frmgaugesimple.ui
