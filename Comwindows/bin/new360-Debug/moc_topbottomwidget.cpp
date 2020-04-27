/****************************************************************************
** Meta object code from reading C++ file 'topbottomwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt360-10.0/src/main/top/topbottomwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'topbottomwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TopBottomWidget_t {
    QByteArrayData data[8];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TopBottomWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TopBottomWidget_t qt_meta_stringdata_TopBottomWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TopBottomWidget"
QT_MOC_LITERAL(1, 16, 16), // "payinsureClicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 15), // "securityClicked"
QT_MOC_LITERAL(4, 50, 14), // "examineClicked"
QT_MOC_LITERAL(5, 65, 11), // "viewClicked"
QT_MOC_LITERAL(6, 77, 16), // "setStackedButton"
QT_MOC_LITERAL(7, 94, 5) // "index"

    },
    "TopBottomWidget\0payinsureClicked\0\0"
    "securityClicked\0examineClicked\0"
    "viewClicked\0setStackedButton\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TopBottomWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,
       4,    0,   41,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void TopBottomWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TopBottomWidget *_t = static_cast<TopBottomWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->payinsureClicked(); break;
        case 1: _t->securityClicked(); break;
        case 2: _t->examineClicked(); break;
        case 3: _t->viewClicked(); break;
        case 4: _t->setStackedButton((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TopBottomWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TopBottomWidget::payinsureClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TopBottomWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TopBottomWidget::securityClicked)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TopBottomWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TopBottomWidget::examineClicked)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TopBottomWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TopBottomWidget::viewClicked)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject TopBottomWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TopBottomWidget.data,
      qt_meta_data_TopBottomWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TopBottomWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TopBottomWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TopBottomWidget.stringdata0))
        return static_cast<void*>(const_cast< TopBottomWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int TopBottomWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void TopBottomWidget::payinsureClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TopBottomWidget::securityClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void TopBottomWidget::examineClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void TopBottomWidget::viewClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
