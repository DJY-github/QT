#-------------------------------------------------
#
# Project created by QtCreator 2017-02-08T16:19:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = sliderselect
TEMPLATE    = app
DESTDIR     = $$PWD/../bin
CONFIG      += warn_off

SOURCES     += main.cpp
SOURCES     += frmsliderselect.cpp
SOURCES     += sliderselect.cpp

HEADERS     += frmsliderselect.h
HEADERS     += sliderselect.h

FORMS       += frmsliderselect.ui
