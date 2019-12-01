#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:19:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugecompass
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugecompass.cpp
SOURCES     += gaugecompass.cpp

HEADERS     += frmgaugecompass.h
HEADERS     += gaugecompass.h

FORMS       += frmgaugecompass.ui
