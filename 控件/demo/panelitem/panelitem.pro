#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:50:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = panelwidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmpanelitem.cpp
SOURCES     += panelitem.cpp

HEADERS     += frmpanelitem.h
HEADERS     += panelitem.h

FORMS       += frmpanelitem.ui
