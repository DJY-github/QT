#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:39:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = navprogress
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmnavprogress.cpp
SOURCES     += navprogress.cpp

HEADERS     += frmnavprogress.h
HEADERS     += navprogress.h

FORMS       += frmnavprogress.ui

RESOURCES   += main.qrc
