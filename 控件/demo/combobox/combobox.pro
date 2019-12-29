#-------------------------------------------------
#
# Project created by QtCreator 2017-04-13T23:50:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = combobox
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcombobox.cpp
SOURCES     += colorcombobox.cpp
SOURCES     += combobox.cpp

HEADERS     += frmcombobox.h
HEADERS     += colorcombobox.h
HEADERS     += combobox.h

FORMS       += frmcombobox.ui

INCLUDEPATH += $$PWD