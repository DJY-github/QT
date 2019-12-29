#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:12:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = navtitle
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += iconhelper.cpp
SOURCES     += frmnavtitle.cpp
SOURCES     += navtitle.cpp

HEADERS     += frmnavtitle.h
HEADERS     += iconhelper.h
HEADERS     += navtitle.h

FORMS       += frmnavtitle.ui

RESOURCES   += main.qrc
