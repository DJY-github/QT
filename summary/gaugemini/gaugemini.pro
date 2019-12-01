#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:22:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugemini
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugemini.cpp
SOURCES     += gaugemini.cpp

HEADERS     += frmgaugemini.h
HEADERS     += gaugemini.h

FORMS       += frmgaugemini.ui
