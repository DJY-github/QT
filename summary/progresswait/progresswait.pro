#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:04:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = progresswait
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmprogresswait.cpp
SOURCES     += progresswait.cpp

HEADERS     += frmprogresswait.h
HEADERS     += progresswait.h

FORMS       += frmprogresswait.ui
