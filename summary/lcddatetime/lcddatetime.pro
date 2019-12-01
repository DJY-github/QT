#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:46:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = lcddatetime
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmlcddatetime.cpp
SOURCES     += lcddatetime.cpp

HEADERS     += frmlcddatetime.h
HEADERS     += lcddatetime.h

FORMS       += frmlcddatetime.ui
