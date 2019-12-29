#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:24:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = animationbutton
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmanimationbutton.cpp
SOURCES     += animationbutton1.cpp
SOURCES     += animationbutton2.cpp

HEADERS     += frmanimationbutton.h
HEADERS     += animationbutton1.h
HEADERS     += animationbutton2.h

FORMS       += frmanimationbutton.ui

RESOURCES   += main.qrc
