QT += network xml svg
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += designer
} else {
    CONFIG += designer
}

target.path         = $$[QT_INSTALL_PLUGINS]/designer
TARGET              = $$qtLibraryTarget(quc)
TEMPLATE            = lib
#RC_FILE             = main.rc

RESOURCES           += image.qrc ico.qrc svg.qrc
INSTALLS            += target
CONFIG              += plugin debug_and_release warn_off
DEFINES             += quc
LIBS                += -L.

MOC_DIR             = temp/moc
RCC_DIR             = temp/rcc
UI_DIR              = temp/ui
OBJECTS_DIR         = temp/obj
DESTDIR             = $$PWD/../bin

include             (src/src.pri)
include             (plugin/plugin.pri)
include             (include/include.pri)

INCLUDEPATH         += $$PWD
INCLUDEPATH         += $$PWD/src
INCLUDEPATH         += $$PWD/plugin
INCLUDEPATH         += $$PWD/include

win32 {
    src_file = $$PWD/../bin/quc.dll
    dst_file = $(QTDIR)/plugins/designer
    src_file ~= s,/,\\,g
    dst_file ~= s,/,\\,g
    QMAKE_POST_LINK += copy $$src_file $$dst_file
}
unix:!macx {
    src_file = $$PWD/../bin/libquc.so
    dst_file = $(QTDIR)/plugins/designer
    QMAKE_POST_LINK += cp -r -f $$src_file $$dst_file
}
macx {
    src_file = $$PWD/../bin/libquc.dylib
    dst_file = $(QTDIR)/plugins/designer
    QMAKE_POST_LINK += cp -r -f $$src_file $$dst_file
}
