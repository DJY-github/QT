#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:21:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = customring
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcustomring.cpp
SOURCES     += customring.cpp

HEADERS     += frmcustomring.h
HEADERS     += customring.h

FORMS       += frmcustomring.ui
