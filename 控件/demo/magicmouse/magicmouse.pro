#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:24:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = magicmouse
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmmagicmouse.cpp
SOURCES     += magicmouse.cpp

HEADERS     += frmmagicmouse.h
HEADERS     += magicmouse.h

FORMS       += frmmagicmouse.ui
