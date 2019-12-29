#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T11:38:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = imageclock
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmimageclock.cpp
SOURCES     += imageclock.cpp

HEADERS     += frmimageclock.h
HEADERS     += imageclock.h

FORMS       += frmimageclock.ui

RESOURCES   += main.qrc
