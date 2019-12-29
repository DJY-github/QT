#-------------------------------------------------
#
# Project created by QtCreator 2017-11-19T22:53:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = colorbutton
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcolorbutton.cpp
SOURCES     += colorbutton.cpp

HEADERS     += frmcolorbutton.h
HEADERS     += colorbutton.h

FORMS       += frmcolorbutton.ui

RESOURCES   += main.qrc
