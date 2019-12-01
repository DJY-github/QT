#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:55:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugecircle
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += gaugecircle.cpp
SOURCES     += frmgaugecircle.cpp

HEADERS     += gaugecircle.h
HEADERS     += frmgaugecircle.h

FORMS       += frmgaugecircle.ui
