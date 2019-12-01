#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:21:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = custompie
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcustompie.cpp
SOURCES     += custompie.cpp

HEADERS     += frmcustompie.h
HEADERS     += custompie.h

FORMS       += frmcustompie.ui
