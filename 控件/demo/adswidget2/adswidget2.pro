#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:21:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = adswidget2
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmadswidget2.cpp
SOURCES     += adswidget2.cpp

HEADERS     += frmadswidget2.h
HEADERS     += adswidget2.h

FORMS       += frmadswidget2.ui

RESOURCES   += main.qrc
