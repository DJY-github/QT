DEFINES += LICENSE_LIBRARY NRLICENSE_DLL
DEFINES += QT_DEPRECATED_WARNINGS

QT_VERSION = 1.0.0

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32 {
DEFINES +=  WIN32 _WIN32 WAVELICENSE_DLL
LIBS	+= -lnetapi32
}

HEADERS += \
    $$PWD/nrlicense.h \
    $$PWD/nrlicense_p.h

SOURCES += \
    $$PWD/nrlicense.cpp
