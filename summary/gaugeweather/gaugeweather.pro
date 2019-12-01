#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:22:04
#
#-------------------------------------------------

QT       += core gui xml svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugeweather
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugeweather.cpp
SOURCES     += gaugeweather.cpp

HEADERS     += frmgaugeweather.h
HEADERS     += gaugeweather.h

FORMS       += frmgaugeweather.ui

RESOURCES   += main.qrc
