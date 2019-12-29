#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:49:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = bottomwidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmbottomwidget.cpp
SOURCES     += bottomwidget.cpp

HEADERS     += frmbottomwidget.h
HEADERS     += bottomwidget.h

FORMS       += frmbottomwidget.ui
