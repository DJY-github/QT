#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:15:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = navlistview
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmnavlistview.cpp
SOURCES     += navlistview.cpp
SOURCES     += frmnavlistviewform.cpp

HEADERS     += frmnavlistview.h
HEADERS     += navlistview.h
HEADERS     += frmnavlistviewform.h

FORMS       += frmnavlistview.ui
FORMS       += frmnavlistviewform.ui

RESOURCES   += main.qrc
