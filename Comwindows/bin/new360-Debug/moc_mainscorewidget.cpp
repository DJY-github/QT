/****************************************************************************
** Meta object code from reading C++ file 'mainscorewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt360-10.0/src/main/top/mainscorewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainscorewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainScoreWidget_t {
    QByteArrayData data[5];
    char stringdata0[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainScoreWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainScoreWidget_t qt_meta_stringdata_MainScoreWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "MainScoreWidget"
QT_MOC_LITERAL(1, 16, 13), // "cancleExamine"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 6), // "oneFix"
QT_MOC_LITERAL(4, 38, 9) // "reExamine"

    },
    "MainScoreWidget\0cancleExamine\0\0oneFix\0"
    "reExamine"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainScoreWidget[] = {

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

void MainScoreWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainScoreWidget *_t = static_cast<MainScoreWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cancleExamine(); break;
        case 1: _t->oneFix(); break;
        case 2: _t->reExamine(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainScoreWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainScoreWidget::cancleExamine)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainScoreWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainScoreWidget::oneFix)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MainScoreWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainScoreWidget::reExamine)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainScoreWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MainScoreWidget.data,
      qt_meta_data_MainScoreWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainScoreWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainScoreWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainScoreWidget.stringdata0))
        return static_cast<void*>(const_cast< MainScoreWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MainScoreWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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

// SIGNAL 0
void MainScoreWidget::cancleExamine()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainScoreWidget::oneFix()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainScoreWidget::reExamine()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
