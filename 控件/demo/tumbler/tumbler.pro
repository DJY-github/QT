#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:37:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = tumbler
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmtumbler.cpp
SOURCES     += frmtumblerdatetime.cpp
SOURCES     += tumblerdatetime.cpp
SOURCES     += tumbler.cpp

HEADERS     += frmtumbler.h
HEADERS     += frmtumblerdatetime.h
HEADERS     += tumblerdatetime.h
HEADERS     += tumbler.h

FORMS       += frmtumbler.ui
FORMS       += frmtumblerdatetime.ui
