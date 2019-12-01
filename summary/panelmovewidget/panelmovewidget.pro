#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:47:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = panelmovewidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmpanelmovewidget.cpp
SOURCES     += lightbutton.cpp

HEADERS     += frmpanelmovewidget.h
HEADERS     += lightbutton.h

FORMS       += frmpanelmovewidget.ui
