#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:08:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = videoplayback
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmvideoplayback.cpp
SOURCES     += videoplayback.cpp

HEADERS     += frmvideoplayback.h
HEADERS     += videoplayback.h

FORMS       += frmvideoplayback.ui
