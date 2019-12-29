#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:52:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugeround
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugeround.cpp
SOURCES     += gaugeround.cpp

HEADERS     += frmgaugeround.h
HEADERS     += gaugeround.h

FORMS       += frmgaugeround.ui
