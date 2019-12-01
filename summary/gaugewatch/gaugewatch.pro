#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T11:14:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugewatch
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugewatch.cpp
SOURCES     += gaugewatch.cpp

HEADERS     += frmgaugewatch.h
HEADERS     += gaugewatch.h

FORMS       += frmgaugewatch.ui
