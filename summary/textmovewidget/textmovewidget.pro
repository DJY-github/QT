#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:34:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = textmovewidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmtextmovewidget.cpp
SOURCES     += textmovewidget.cpp

HEADERS     += frmtextmovewidget.h
HEADERS     += textmovewidget.h

FORMS       += frmtextmovewidget.ui
