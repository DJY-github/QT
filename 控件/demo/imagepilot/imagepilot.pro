#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T14:36:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = imagepilot
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmimagepilot.cpp
SOURCES     += imagepilot.cpp

HEADERS     += frmimagepilot.h
HEADERS     += imagepilot.h

FORMS       += frmimagepilot.ui

RESOURCES   += main.qrc
