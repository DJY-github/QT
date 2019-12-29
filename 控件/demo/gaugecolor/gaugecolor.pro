#-------------------------------------------------
#
# Project created by QtCreator 2016-12-16T16:18:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugecolor
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugecolor.cpp
SOURCES     += gaugecolor.cpp

HEADERS     += frmgaugecolor.h
HEADERS     += gaugecolor.h

FORMS       += frmgaugecolor.ui
