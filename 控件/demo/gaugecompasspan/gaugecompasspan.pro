#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:22:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugecompasspan
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugecompasspan.cpp
SOURCES     += gaugecompasspan.cpp

HEADERS     += frmgaugecompasspan.h
HEADERS     += gaugecompasspan.h

FORMS       += frmgaugecompasspan.ui
