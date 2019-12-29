#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:46:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = oventimer
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmoventimer.cpp
SOURCES     += oventimer.cpp

HEADERS     += frmoventimer.h
HEADERS     += oventimer.h

FORMS       += frmoventimer.ui
