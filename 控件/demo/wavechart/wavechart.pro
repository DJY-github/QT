#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:56:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = wavechart
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp \
    smoothcurvecreator.cpp
SOURCES     += frmwavechart.cpp
SOURCES     += wavechart.cpp

HEADERS     += frmwavechart.h \
    smoothcurvecreator.h
HEADERS     += wavechart.h

FORMS       += frmwavechart.ui
