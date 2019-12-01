#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:22:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugedial
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugedial.cpp
SOURCES     += gaugedial.cpp

HEADERS     += frmgaugedial.h
HEADERS     += gaugedial.h

FORMS       += frmgaugedial.ui
