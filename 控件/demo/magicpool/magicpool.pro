#-------------------------------------------------
#
# Project created by QtCreator 2018-7-14T10:23:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = magicpool
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += magicpool.cpp
SOURCES     += frmmagicpool.cpp

HEADERS     += magicpool.h
HEADERS     += frmmagicpool.h

FORMS       += frmmagicpool.ui
