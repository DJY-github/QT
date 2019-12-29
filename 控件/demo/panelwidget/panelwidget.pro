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
SOURCES     += frmpanelwidget.cpp
SOURCES     += frmpanelwidgetx.cpp
SOURCES     += gaugeprogress.cpp
SOURCES     += lightbutton.cpp
SOURCES     += panelwidget.cpp

HEADERS     += frmpanelwidget.h
HEADERS     += frmpanelwidgetx.h
HEADERS     += gaugeprogress.h
HEADERS     += lightbutton.h
HEADERS     += panelwidget.h

FORMS       += frmpanelwidget.ui
FORMS       += frmpanelwidgetx.ui
