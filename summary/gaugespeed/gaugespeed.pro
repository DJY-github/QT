#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T11:05:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugespeed
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugespeed.cpp
SOURCES     += gaugespeed.cpp

HEADERS     += frmgaugespeed.h
HEADERS     += gaugespeed.h

FORMS       += frmgaugespeed.ui

RESOURCES   += main.qrc
