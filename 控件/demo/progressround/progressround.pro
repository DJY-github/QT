#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:59:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = progressround
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogressround.cpp
SOURCES     += progressround.cpp

HEADERS     += frmprogressround.h
HEADERS     += progressround.h

FORMS       += frmprogressround.ui
