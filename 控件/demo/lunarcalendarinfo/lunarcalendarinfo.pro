#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:08:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = lunarcalendarinfo
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmlunarcalendarinfo.cpp
SOURCES     += lunarcalendarinfo.cpp

HEADERS     += frmlunarcalendarinfo.h
HEADERS     += lunarcalendarinfo.h

FORMS       += frmlunarcalendarinfo.ui
