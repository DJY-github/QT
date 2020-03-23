#-------------------------------------------------
#
# Project created by QtCreator 2010-05-26T09:29:42
#
#-------------------------------------------------

QT       += core gui widgets multimedia

TARGET = Tester
TEMPLATE = app


SOURCES += main.cpp \
    keyboard/widgetKeyBoard.cpp \
    keyboard/QKeyPushButton.cpp \
    examplemyfocus.cpp \
    tester.cpp

HEADERS  += examplemyfocus.h \
    keyboard/widgetKeyBoard.h \
    keyboard/QKeyPushButton.h \
    tester.h

FORMS    += \
    tester.ui

TRANSLATIONS += virtualBoard_it.ts \
    virtualBoard_ru.ts \
    virtualBoard_fr.ts \
    virtualBoard_en.ts

unix {    
    QMAKE_POST_LINK = lrelease widgetKeyboard2010.pro
}

RESOURCES += virtualboard.qrc
