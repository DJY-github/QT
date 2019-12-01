#-------------------------------------------------
#
# Project created by QtCreator 2017-01-07T12:06:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugearc
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugearc.cpp
SOURCES     += gaugearc.cpp

HEADERS     += frmgaugearc.h
HEADERS     += gaugearc.h

FORMS       += frmgaugearc.ui

RESOURCES   += main.qrc
