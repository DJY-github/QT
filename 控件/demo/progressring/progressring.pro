#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T10:14:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = progressring
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogressring.cpp
SOURCES     += progressring.cpp

HEADERS     += frmprogressring.h
HEADERS     += progressring.h

FORMS       += frmprogressring.ui
