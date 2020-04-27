/****************************************************************************
** Meta object code from reading C++ file 'sysbuttongroup.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt360-10.0/src/commom/sysbuttongroup.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sysbuttongroup.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SysButtonGroup_t {
    QByteArrayData data[7];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SysButtonGroup_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SysButtonGroup_t qt_meta_stringdata_SysButtonGroup = {
    {
QT_MOC_LITERAL(0, 0, 14), // "SysButtonGroup"
QT_MOC_LITERAL(1, 15, 9), // "playVideo"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 8), // "showSkin"
QT_MOC_LITERAL(4, 35, 8), // "showMenu"
QT_MOC_LITERAL(5, 44, 7), // "showMin"
QT_MOC_LITERAL(6, 52, 11) // "closeWidget"

    },
    "SysButtonGroup\0playVideo\0\0showSkin\0"
    "showMenu\0showMin\0closeWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SysButtonGroup[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,
       6,    0,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SysButtonGroup::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SysButtonGroup *_t = static_cast<SysButtonGroup *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->playVideo(); break;
        case 1: _t->showSkin(); break;
        case 2: _t->showMenu(); break;
        case 3: _t->showMin(); break;
        case 4: _t->closeWidget(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SysButtonGroup::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SysButtonGroup::playVideo)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SysButtonGroup::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SysButtonGroup::showSkin)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (SysButtonGroup::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SysButtonGroup::showMenu)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (SysButtonGroup::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SysButtonGroup::showMin)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (SysButtonGroup::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SysButtonGroup::closeWidget)) {
                *result = 4;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SysButtonGroup::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SysButtonGroup.data,
      qt_meta_data_SysButtonGroup,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SysButtonGroup::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SysButtonGroup::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SysButtonGroup.stringdata0))
        return static_cast<void*>(const_cast< SysButtonGroup*>(this));
    return QWidget::qt_metacast(_clname);
}

int SysButtonGroup::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SysButtonGroup::playVideo()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SysButtonGroup::showSkin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SysButtonGroup::showMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SysButtonGroup::showMin()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SysButtonGroup::closeWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
