/****************************************************************************
** Meta object code from reading C++ file 'animbuttonwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt360-10.0/src/commom/animbuttonwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'animbuttonwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AnimButtonWidget_t {
    QByteArrayData data[7];
    char stringdata0[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AnimButtonWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AnimButtonWidget_t qt_meta_stringdata_AnimButtonWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "AnimButtonWidget"
QT_MOC_LITERAL(1, 17, 10), // "setOriginX"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 1), // "x"
QT_MOC_LITERAL(4, 31, 7), // "setEndX"
QT_MOC_LITERAL(5, 39, 11), // "leaveButton"
QT_MOC_LITERAL(6, 51, 10) // "updateAnim"

    },
    "AnimButtonWidget\0setOriginX\0\0x\0setEndX\0"
    "leaveButton\0updateAnim"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AnimButtonWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    1,   37,    2, 0x0a /* Public */,
       5,    0,   40,    2, 0x0a /* Public */,
       6,    0,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AnimButtonWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AnimButtonWidget *_t = static_cast<AnimButtonWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setOriginX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->setEndX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->leaveButton(); break;
        case 3: _t->updateAnim(); break;
        default: ;
        }
    }
}

const QMetaObject AnimButtonWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AnimButtonWidget.data,
      qt_meta_data_AnimButtonWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AnimButtonWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AnimButtonWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AnimButtonWidget.stringdata0))
        return static_cast<void*>(const_cast< AnimButtonWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int AnimButtonWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
