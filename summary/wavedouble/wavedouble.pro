#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:44:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = wavedouble
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmwavedouble.cpp
SOURCES     += wavedouble.cpp

HEADERS     += frmwavedouble.h
HEADERS     += wavedouble.h

FORMS       += frmwavedouble.ui
