#-------------------------------------------------
#
# Project created by QtCreator 2017-01-12T10:09:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = waveplot
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmwaveplot.cpp
SOURCES     += waveplot.cpp

HEADERS     += frmwaveplot.h
HEADERS     += waveplot.h

FORMS       += frmwaveplot.ui
