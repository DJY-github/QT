/****************************************************************************
** Meta object code from reading C++ file 'mygauge7.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mygauge7.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mygauge7.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myGauge7_t {
    QByteArrayData data[7];
    char stringdata0[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myGauge7_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myGauge7_t qt_meta_stringdata_myGauge7 = {
    {
QT_MOC_LITERAL(0, 0, 8), // "myGauge7"
QT_MOC_LITERAL(1, 9, 11), // "UpdateGraph"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "setValue"
QT_MOC_LITERAL(4, 31, 5), // "value"
QT_MOC_LITERAL(5, 37, 12), // "setMarkColor"
QT_MOC_LITERAL(6, 50, 3) // "clr"

    },
    "myGauge7\0UpdateGraph\0\0setValue\0value\0"
    "setMarkColor\0clr"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myGauge7[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    1,   30,    2, 0x0a /* Public */,
       5,    1,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QReal,    4,
    QMetaType::Void, QMetaType::QColor,    6,

       0        // eod
};

void myGauge7::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myGauge7 *_t = static_cast<myGauge7 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpdateGraph(); break;
        case 1: _t->setValue((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 2: _t->setMarkColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject myGauge7::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_myGauge7.data,
      qt_meta_data_myGauge7,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *myGauge7::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myGauge7::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_myGauge7.stringdata0))
        return static_cast<void*>(const_cast< myGauge7*>(this));
    return QWidget::qt_metacast(_clname);
}

int myGauge7::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
