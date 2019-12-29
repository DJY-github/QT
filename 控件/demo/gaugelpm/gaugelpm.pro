#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:14:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = gaugelpm
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmgaugelpm.cpp
SOURCES     += gaugelpm.cpp

HEADERS     += frmgaugelpm.h
HEADERS     += gaugelpm.h

FORMS       += frmgaugelpm.ui
