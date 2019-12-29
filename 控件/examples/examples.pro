#-------------------------------------------------
#
# Project created by QtCreator 2016-12-17T11:38:51
#
#-------------------------------------------------

QT       += core gui network xml svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET              = examples
TEMPLATE            = app
MOC_DIR             = temp/moc
RCC_DIR             = temp/rcc
UI_DIR              = temp/ui
OBJECTS_DIR         = temp/obj
DESTDIR             = $$PWD/../bin
PRECOMPILED_HEADER  = head.h
RC_FILE             = other/main.rc

#如果定义了alone则表示以源码形式集成编译到examples中,否则以控件以插件形式集成
#一般编译android版本需要改成alone
DEFINES             += alone1
CONFIG              += warn_off
SOURCES             += main.cpp
RESOURCES           += other/main.qrc

contains(DEFINES, alone) {
include     ($$PWD/../designer/include/include.pri)
include     ($$PWD/../designer/src/src.pri)
INCLUDEPATH += $$PWD/../designer/include
INCLUDEPATH += $$PWD/../designer/src
RESOURCES   += $$PWD/../designer/image.qrc
RESOURCES   += $$PWD/../designer/svg.qrc
RESOURCES   += $$PWD/../designer/ico.qrc
} else {
INCLUDEPATH += $$PWD/../designer/include
CONFIG(release, debug|release){
LIBS        += -L$$PWD/../bin/ -lquc
} else {
#MAC系统可能要改成 -lquc_debug
unix {LIBS  += -L$$PWD/../bin/ -lquc}
else {LIBS  += -L$$PWD/../bin/ -lqucd}
}
}

include     ($$PWD/frmmain/frmmain.pri)
include     ($$PWD/frmgauge/frmgauge.pri)
include     ($$PWD/frmprogress/frmprogress.pri)
include     ($$PWD/frmnav/frmnav.pri)
include     ($$PWD/frmwave/frmwave.pri)
include     ($$PWD/frmruler/frmruler.pri)
include     ($$PWD/frmslider/frmslider.pri)
include     ($$PWD/frmbar/frmbar.pri)
include     ($$PWD/frmcolor/frmcolor.pri)
include     ($$PWD/frmimage/frmimage.pri)
include     ($$PWD/frmpainter/frmpainter.pri)
include     ($$PWD/frmother/frmother.pri)
include     ($$PWD/frmdemo/frmdemo.pri)
include     ($$PWD/frmvideo/frmvideo.pri)
include     ($$PWD/frmx/frmx.pri)
include     ($$PWD/frmcommon/frmcommon.pri)

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/frmmain
INCLUDEPATH += $$PWD/frmgauge
INCLUDEPATH += $$PWD/frmprogress
INCLUDEPATH += $$PWD/frmnav
INCLUDEPATH += $$PWD/frmwave
INCLUDEPATH += $$PWD/frmruler
INCLUDEPATH += $$PWD/frmslider
INCLUDEPATH += $$PWD/frmbar
INCLUDEPATH += $$PWD/frmcolor
INCLUDEPATH += $$PWD/frmimage
INCLUDEPATH += $$PWD/frmpainter
INCLUDEPATH += $$PWD/frmother
INCLUDEPATH += $$PWD/frmdemo
INCLUDEPATH += $$PWD/frmvideo
INCLUDEPATH += $$PWD/frmx
INCLUDEPATH += $$PWD/frmcommon
