#-------------------------------------------------
#
# Project created by QtCreator 2019-06-09T22:24:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = imageanimation
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmimageanimation.cpp
SOURCES     += imageanimation.cpp

HEADERS     += frmimageanimation.h
HEADERS     += imageanimation.h

FORMS       += frmimageanimation.ui

RESOURCES   += main.qrc
