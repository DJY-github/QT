#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:15:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = navbar
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmnavbar.cpp
SOURCES     += frmnavbarform.cpp
SOURCES     += navbar.cpp

HEADERS     += frmnavbar.h
HEADERS     += frmnavbarform.h
HEADERS     += navbar.h

FORMS       += frmnavbar.ui
FORMS       += frmnavbarform.ui
