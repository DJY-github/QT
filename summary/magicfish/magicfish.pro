#-------------------------------------------------
#
# Project created by QtCreator 2018-7-14T10:23:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = magicfish
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += magicfish.cpp
SOURCES     += colorcombobox.cpp
SOURCES     += frmmagicfish.cpp

HEADERS     += magicfish.h
HEADERS     += colorcombobox.h
HEADERS     += frmmagicfish.h

FORMS       += frmmagicfish.ui
