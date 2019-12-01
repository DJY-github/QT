#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:49:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugerange
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugerange.cpp
SOURCES     += gaugerange.cpp

HEADERS     += frmgaugerange.h
HEADERS     += gaugerange.h

FORMS       += frmgaugerange.ui

RESOURCES   += main.qrc
