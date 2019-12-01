#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:32:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = barvumeter
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmbarvumeter.cpp
SOURCES     += barvumeter.cpp

HEADERS     += frmbarvumeter.h
HEADERS     += barvumeter.h

FORMS       += frmbarvumeter.ui
