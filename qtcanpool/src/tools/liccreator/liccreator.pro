QTC_LIB_DEPENDS += license

QT += core gui

include(../../tool.pri)

TARGET = liccreator

win32|equals(TEST, 1):DEFINES += HAS_MSVC_PARSER

include(liccreator-src.pri)
