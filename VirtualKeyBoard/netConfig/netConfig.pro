#-------------------------------------------------
#
# Project created by QtCreator 2018-10-21T14:55:08
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = netConfig
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    login.cpp \
    usermanger.cpp \
    SoftKeyBoard.cpp \
    SoftKeyBoardContext.cpp \
    frminput.cpp

HEADERS += \
        mainwindow.h \
    login.h \
    usermanger.h \
    SoftKeyBoard.h \
    SoftKeyBoardContext.h \
    frminput.h \
    def.h

FORMS += \
        mainwindow.ui \
    login.ui \
    usermanger.ui \
    SoftKeyBoard.ui \
    frminput.ui
