#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:39:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = tiledbg
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmtiledbg.cpp
SOURCES     += tiledbg.cpp

HEADERS     += frmtiledbg.h
HEADERS     += tiledbg.h

FORMS       += frmtiledbg.ui
