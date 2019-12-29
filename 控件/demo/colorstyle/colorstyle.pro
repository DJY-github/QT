#-------------------------------------------------
#
# Project created by QtCreator 2017-01-12T10:09:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = colorstyle
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcolorstyle.cpp
SOURCES     += colorstyle.cpp

HEADERS     += frmcolorstyle.h
HEADERS     += colorstyle.h

FORMS       += frmcolorstyle.ui

RESOURCES   += main.qrc
