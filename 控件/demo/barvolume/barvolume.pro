#-------------------------------------------------
#
# Project created by QtCreator 2017-01-05T22:11:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = barvolume
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmbarvolume.cpp
SOURCES     += barvolume.cpp

HEADERS     += frmbarvolume.h
HEADERS     += barvolume.h

FORMS       += frmbarvolume.ui
