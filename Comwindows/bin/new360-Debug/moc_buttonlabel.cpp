/****************************************************************************
** Meta object code from reading C++ file 'buttonlabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt360-10.0/src/main/common/buttonlabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'buttonlabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ButtonLabel_t {
    QByteArrayData data[5];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ButtonLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ButtonLabel_t qt_meta_stringdata_ButtonLabel = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ButtonLabel"
QT_MOC_LITERAL(1, 12, 12), // "labelClicked"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 11), // "enterSignal"
QT_MOC_LITERAL(4, 38, 11) // "leaveSignal"

    },
    "ButtonLabel\0labelClicked\0\0enterSignal\0"
    "leaveSignal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ButtonLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,
       4,    0,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ButtonLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ButtonLabel *_t = static_cast<ButtonLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->labelClicked(); break;
        case 1: _t->enterSignal(); break;
        case 2: _t->leaveSignal(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ButtonLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ButtonLabel::labelClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ButtonLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ButtonLabel::enterSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ButtonLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ButtonLabel::leaveSignal)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ButtonLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_ButtonLabel.data,
      qt_meta_data_ButtonLabel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ButtonLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ButtonLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ButtonLabel.stringdata0))
        return static_cast<void*>(const_cast< ButtonLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int ButtonLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ButtonLabel::labelClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ButtonLabel::enterSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ButtonLabel::leaveSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
