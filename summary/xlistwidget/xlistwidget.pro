#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T15:50:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = xlistwidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += xlistwidget.cpp
SOURCES     += iconfont.cpp
SOURCES     += frmxlistwidget.cpp
HEADERS     += frmxlistwidget.h
HEADERS     += xlistwidget.h
HEADERS     += iconfont.h
FORMS       += frmxlistwidget.ui
RESOURCES   += main.qrc
