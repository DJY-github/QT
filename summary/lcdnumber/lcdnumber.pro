#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T14:48:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = lcdnumber
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmlcdnumber.cpp
SOURCES     += lcdnumber.cpp

HEADERS     += frmlcdnumber.h
HEADERS     += lcdnumber.h

FORMS       += frmlcdnumber.ui
