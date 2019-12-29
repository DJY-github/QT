#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:54:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = progressplay
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogressplay.cpp
SOURCES     += progressplay.cpp

HEADERS     += frmprogressplay.h
HEADERS     += progressplay.h

FORMS       += frmprogressplay.ui
