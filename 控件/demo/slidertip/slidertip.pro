#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:19:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = slidertip
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmslidertip.cpp
SOURCES     += slidertip.cpp
SOURCES     += navlabel.cpp
SOURCES     += flatui.cpp

HEADERS     += frmslidertip.h
HEADERS     += slidertip.h
HEADERS     += navlabel.h
HEADERS     += flatui.h

FORMS       += frmslidertip.ui
