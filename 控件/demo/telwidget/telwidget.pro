#-------------------------------------------------
#
# Project created by QtCreator 2018-10-08T15:50:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET          = telwidget
TEMPLATE        = app
MOC_DIR         = temp/moc
RCC_DIR         = temp/rcc
UI_DIR          = temp/ui
OBJECTS_DIR     = temp/obj
DESTDIR         = $$PWD/../bin
CONFIG          += warn_off
RESOURCES       += main.qrc

SOURCES         += main.cpp
SOURCES         += zhtopy.cpp
SOURCES         += telwidget.cpp
SOURCES         += frmtelwidget.cpp

HEADERS         += telwidget.h
HEADERS         += zhtopy.h
HEADERS         += frmtelwidget.h

FORMS           += frmtelwidget.ui

INCLUDEPATH     += $$PWD
