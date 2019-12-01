#-------------------------------------------------
#
# Project created by QtCreator 2017-11-19T22:53:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugeplane
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += gaugeplane.cpp
SOURCES     += frmgaugeplane.cpp

HEADERS     += frmgaugeplane.h
HEADERS     += gaugeplane.h

FORMS       += frmgaugeplane.ui
