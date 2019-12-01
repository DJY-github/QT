#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T09:52:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = cpumemorylabel
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmcpumemorylabel.cpp
SOURCES     += cpumemorylabel.cpp

HEADERS     += frmcpumemorylabel.h
HEADERS     += cpumemorylabel.h

FORMS       += frmcpumemorylabel.ui
