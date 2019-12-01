#-------------------------------------------------
#
# Project created by QtCreator 2017-11-19T22:40:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = colorpanel
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcolorpanel.cpp
SOURCES     += wkbutton.cpp
SOURCES     += colorpanelbtn.cpp
SOURCES     += colorpanelbar.cpp
SOURCES     += colorpanelhsb.cpp
SOURCES     += colorpanelfader.cpp

HEADERS     += frmcolorpanel.h
HEADERS     += wkbutton.h
HEADERS     += colorpanelbtn.h
HEADERS     += colorpanelbar.h
HEADERS     += colorpanelhsb.h
HEADERS     += colorpanelfader.h

FORMS       += frmcolorpanel.ui
