#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T14:58:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = ledtext
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmledtext.cpp
SOURCES     += ledtext.cpp

HEADERS     += frmledtext.h
HEADERS     += ledtext.h

FORMS       += frmledtext.ui
