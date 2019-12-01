#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T11:05:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugepanel
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugepanel.cpp
SOURCES     += gaugepanel.cpp

HEADERS     += frmgaugepanel.h
HEADERS     += gaugepanel.h

FORMS       += frmgaugepanel.ui

