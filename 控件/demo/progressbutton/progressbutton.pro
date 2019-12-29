#-------------------------------------------------
#
# Project created by QtCreator 2019-04-17T15:54:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = progressbutton
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogressbutton.cpp
SOURCES     += progressbutton.cpp

HEADERS     += frmprogressbutton.h
HEADERS     += progressbutton.h

FORMS       += frmprogressbutton.ui
