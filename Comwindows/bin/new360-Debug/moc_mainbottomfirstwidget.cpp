/****************************************************************************
** Meta object code from reading C++ file 'mainbottomfirstwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt360-10.0/src/main/bottom/mainbottomfirstwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainbottomfirstwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainBottomFirstWidget_t {
    QByteArrayData data[6];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainBottomFirstWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainBottomFirstWidget_t qt_meta_stringdata_MainBottomFirstWidget = {
    {
QT_MOC_LITERAL(0, 0, 21), // "MainBottomFirstWidget"
QT_MOC_LITERAL(1, 22, 11), // "safeClicked"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 12), // "cleanClicked"
QT_MOC_LITERAL(4, 48, 13), // "youhuaClicked"
QT_MOC_LITERAL(5, 62, 18) // "advtoolMoreClicked"

    },
    "MainBottomFirstWidget\0safeClicked\0\0"
    "cleanClicked\0youhuaClicked\0"
    "advtoolMoreClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainBottomFirstWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    0,   36,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainBottomFirstWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainBottomFirstWidget *_t = static_cast<MainBottomFirstWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->safeClicked(); break;
        case 1: _t->cleanClicked(); break;
        case 2: _t->youhuaClicked(); break;
        case 3: _t->advtoolMoreClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainBottomFirstWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainBottomFirstWidget::safeClicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainBottomFirstWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainBottomFirstWidget::cleanClicked)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MainBottomFirstWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainBottomFirstWidget::youhuaClicked)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MainBottomFirstWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainBottomFirstWidget::advtoolMoreClicked)) {
                *result = 3;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainBottomFirstWidget::staticMetaObject = {
    { &BaseStyleWidget::staticMetaObject, qt_meta_stringdata_MainBottomFirstWidget.data,
      qt_meta_data_MainBottomFirstWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainBottomFirstWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainBottomFirstWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainBottomFirstWidget.stringdata0))
        return static_cast<void*>(const_cast< MainBottomFirstWidget*>(this));
    return BaseStyleWidget::qt_metacast(_clname);
}

int MainBottomFirstWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseStyleWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void MainBottomFirstWidget::safeClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainBottomFirstWidget::cleanClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainBottomFirstWidget::youhuaClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MainBottomFirstWidget::advtoolMoreClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
