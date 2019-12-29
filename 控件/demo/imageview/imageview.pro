#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T14:43:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = imageview
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmimageview.cpp
SOURCES     += imageview.cpp

HEADERS     += frmimageview.h
HEADERS     += imageview.h

FORMS       += frmimageview.ui

RESOURCES   += main.qrc
