#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:21:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = selectwidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmselectwidget.cpp
SOURCES     += selectwidget.cpp

HEADERS     += frmselectwidget.h
HEADERS     += selectwidget.h

FORMS       += frmselectwidget.ui
