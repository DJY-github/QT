#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:22:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugedecibel
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugedecibel.cpp
SOURCES     += gaugedecibel.cpp

HEADERS     += frmgaugedecibel.h
HEADERS     += gaugedecibel.h

FORMS       += frmgaugedecibel.ui
