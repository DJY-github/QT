#-------------------------------------------------
#
# Project created by QtCreator 2017-11-19T22:26:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = colorpanelfader
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcolorpanelfader.cpp
SOURCES     += colorpanelfader.cpp
SOURCES     += colorpanelbar.cpp

HEADERS     += frmcolorpanelfader.h
HEADERS     += colorpanelfader.h
HEADERS     += colorpanelbar.h

FORMS       += frmcolorpanelfader.ui
