/****************************************************************************
** Meta object code from reading C++ file 'animbuttongroupwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt360-10.0/src/commom/animbuttongroupwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'animbuttongroupwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AnimButtonGroupWidget_t {
    QByteArrayData data[10];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AnimButtonGroupWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AnimButtonGroupWidget_t qt_meta_stringdata_AnimButtonGroupWidget = {
    {
QT_MOC_LITERAL(0, 0, 21), // "AnimButtonGroupWidget"
QT_MOC_LITERAL(1, 22, 8), // "turnPage"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 17), // "leaveButtonSignal"
QT_MOC_LITERAL(4, 50, 15), // "setOriginSignal"
QT_MOC_LITERAL(5, 66, 12), // "setEndSignal"
QT_MOC_LITERAL(6, 79, 11), // "clickButton"
QT_MOC_LITERAL(7, 91, 5), // "index"
QT_MOC_LITERAL(8, 97, 11), // "enterButton"
QT_MOC_LITERAL(9, 109, 11) // "leaveButton"

    },
    "AnimButtonGroupWidget\0turnPage\0\0"
    "leaveButtonSignal\0setOriginSignal\0"
    "setEndSignal\0clickButton\0index\0"
    "enterButton\0leaveButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AnimButtonGroupWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       3,    0,   52,    2, 0x06 /* Public */,
       4,    1,   53,    2, 0x06 /* Public */,
       5,    1,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   59,    2, 0x08 /* Private */,
       8,    1,   62,    2, 0x08 /* Private */,
       9,    1,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void AnimButtonGroupWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AnimButtonGroupWidget *_t = static_cast<AnimButtonGroupWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->turnPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->leaveButtonSignal(); break;
        case 2: _t->setOriginSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setEndSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->clickButton((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->enterButton((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->leaveButton((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AnimButtonGroupWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AnimButtonGroupWidget::turnPage)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AnimButtonGroupWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AnimButtonGroupWidget::leaveButtonSignal)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (AnimButtonGroupWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AnimButtonGroupWidget::setOriginSignal)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (AnimButtonGroupWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AnimButtonGroupWidget::setEndSignal)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject AnimButtonGroupWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AnimButtonGroupWidget.data,
      qt_meta_data_AnimButtonGroupWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AnimButtonGroupWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AnimButtonGroupWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AnimButtonGroupWidget.stringdata0))
        return static_cast<void*>(const_cast< AnimButtonGroupWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int AnimButtonGroupWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void AnimButtonGroupWidget::turnPage(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AnimButtonGroupWidget::leaveButtonSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AnimButtonGroupWidget::setOriginSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AnimButtonGroupWidget::setEndSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
