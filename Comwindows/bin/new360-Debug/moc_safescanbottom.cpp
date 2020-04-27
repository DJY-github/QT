/****************************************************************************
** Meta object code from reading C++ file 'safescanbottom.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt360-10.0/src/safe/common/safescanbottom.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'safescanbottom.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SafeScanBottom_t {
    QByteArrayData data[7];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SafeScanBottom_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SafeScanBottom_t qt_meta_stringdata_SafeScanBottom = {
    {
QT_MOC_LITERAL(0, 0, 14), // "SafeScanBottom"
QT_MOC_LITERAL(1, 15, 12), // "quickClicked"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "fullClicked"
QT_MOC_LITERAL(4, 41, 13), // "customClicked"
QT_MOC_LITERAL(5, 55, 10), // "fixClicked"
QT_MOC_LITERAL(6, 66, 12) // "patchClicked"

    },
    "SafeScanBottom\0quickClicked\0\0fullClicked\0"
    "customClicked\0fixClicked\0patchClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SafeScanBottom[] = {

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

void SafeScanBottom::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SafeScanBottom *_t = static_cast<SafeScanBottom *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->quickClicked(); break;
        case 1: _t->fullClicked(); break;
        case 2: _t->customClicked(); break;
        case 3: _t->fixClicked(); break;
        case 4: _t->patchClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SafeScanBottom::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SafeScanBottom::quickClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SafeScanBottom::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SafeScanBottom::fullClicked)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (SafeScanBottom::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SafeScanBottom::customClicked)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (SafeScanBottom::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SafeScanBottom::fixClicked)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (SafeScanBottom::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SafeScanBottom::patchClicked)) {
                *result = 4;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SafeScanBottom::staticMetaObject = {
    { &BaseStyleWidget::staticMetaObject, qt_meta_stringdata_SafeScanBottom.data,
      qt_meta_data_SafeScanBottom,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SafeScanBottom::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SafeScanBottom::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SafeScanBottom.stringdata0))
        return static_cast<void*>(const_cast< SafeScanBottom*>(this));
    return BaseStyleWidget::qt_metacast(_clname);
}

int SafeScanBottom::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseStyleWidget::qt_metacall(_c, _id, _a);
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
void SafeScanBottom::quickClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SafeScanBottom::fullClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SafeScanBottom::customClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SafeScanBottom::fixClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SafeScanBottom::patchClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
