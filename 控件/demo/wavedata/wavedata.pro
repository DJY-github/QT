#-------------------------------------------------
#
# Project created by QtCreator 2017-01-12T10:09:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = wavedata
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += smoothcurvecreator.cpp
SOURCES     += frmwavedata.cpp
SOURCES     += wavedata.cpp

HEADERS     += frmwavedata.h
HEADERS     += smoothcurvecreator.h
HEADERS     += wavedata.h

FORMS       += frmwavedata.ui

RESOURCES   += main.qrc
