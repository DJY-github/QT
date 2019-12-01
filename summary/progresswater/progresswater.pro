#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T11:05:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = progresswater
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogresswater.cpp
SOURCES     += progresswater.cpp

HEADERS     += frmprogresswater.h
HEADERS     += progresswater.h

FORMS       += frmprogresswater.ui
