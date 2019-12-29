#-------------------------------------------------
#
# Project created by QtCreator 2019-03-28T09:46:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = customrocker
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcustomrocker.cpp
SOURCES     += customrocker.cpp

HEADERS     += frmcustomrocker.h
HEADERS     += customrocker.h

FORMS       += frmcustomrocker.ui
