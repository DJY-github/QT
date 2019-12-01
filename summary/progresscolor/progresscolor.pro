#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:54:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = progresscolor
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogresscolor.cpp
SOURCES     += progresscolor.cpp

HEADERS     += frmprogresscolor.h
HEADERS     += progresscolor.h

FORMS       += frmprogresscolor.ui
