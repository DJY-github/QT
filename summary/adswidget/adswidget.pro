#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:21:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = adswidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmadswidget.cpp
SOURCES     += adswidget.cpp

HEADERS     += frmadswidget.h
HEADERS     += adswidget.h

FORMS       += frmadswidget.ui

RESOURCES   += main.qrc
