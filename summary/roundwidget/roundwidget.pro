#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:13:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = roundwidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmroundwidget.cpp
SOURCES     += roundwidget.cpp

HEADERS     += frmroundwidget.h
HEADERS     += roundwidget.h

FORMS       += frmroundwidget.ui
