#-------------------------------------------------
#
# Project created by QtCreator 2017-01-05T22:11:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = videowidget
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmvideowidget.cpp
SOURCES     += videowidget.cpp

HEADERS     += frmvideowidget.h
HEADERS     += videowidget.h

FORMS       += frmvideowidget.ui
