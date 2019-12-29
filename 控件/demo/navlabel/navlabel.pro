#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:12:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = navlabel
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmnavlabel.cpp
SOURCES     += navlabel.cpp

HEADERS     += frmnavlabel.h
HEADERS     += navlabel.h

FORMS       += frmnavlabel.ui
