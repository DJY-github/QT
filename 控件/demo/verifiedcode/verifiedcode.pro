#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:40:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = verifiedcode
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmverifiedcode.cpp
SOURCES     += verifiedcode.cpp

HEADERS     += frmverifiedcode.h
HEADERS     += verifiedcode.h

FORMS       += frmverifiedcode.ui
