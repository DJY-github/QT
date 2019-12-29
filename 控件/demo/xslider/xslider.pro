#-------------------------------------------------
#
# Project created by QtCreator 2019-01-16T10:16:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = xslider
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmxslider.cpp
SOURCES     += xslider.cpp

HEADERS     += frmxslider.h
HEADERS     += xslider.h

FORMS       += frmxslider.ui
