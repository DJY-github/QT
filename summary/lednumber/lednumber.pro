#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T14:53:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = lednumber
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmlednumber.cpp
SOURCES     += lednumber.cpp

HEADERS     += frmlednumber.h
HEADERS     += lednumber.h

FORMS       += frmlednumber.ui
