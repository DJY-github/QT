#-------------------------------------------------
#
# Project created by QtCreator 2017-02-13T12:39:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = iconeditor
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmiconeditor.cpp
SOURCES     += iconeditor.cpp

HEADERS     += frmiconeditor.h
HEADERS     += iconeditor.h

FORMS       += frmiconeditor.ui
