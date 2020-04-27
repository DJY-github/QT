/****************************************************************************
** Meta object code from reading C++ file 'maintopwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt360-10.0/src/main/maintopwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maintopwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainTopWidget_t {
    QByteArrayData data[15];
    char stringdata0[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainTopWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainTopWidget_t qt_meta_stringdata_MainTopWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "MainTopWidget"
QT_MOC_LITERAL(1, 14, 9), // "playVideo"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 8), // "showSkin"
QT_MOC_LITERAL(4, 34, 8), // "showMenu"
QT_MOC_LITERAL(5, 43, 7), // "showMin"
QT_MOC_LITERAL(6, 51, 11), // "closeWidget"
QT_MOC_LITERAL(7, 63, 9), // "goExamine"
QT_MOC_LITERAL(8, 73, 6), // "goMain"
QT_MOC_LITERAL(9, 80, 7), // "setNums"
QT_MOC_LITERAL(10, 88, 3), // "num"
QT_MOC_LITERAL(11, 92, 14), // "examineClicked"
QT_MOC_LITERAL(12, 107, 11), // "viewClicked"
QT_MOC_LITERAL(13, 119, 10), // "returnMain"
QT_MOC_LITERAL(14, 130, 23) // "returnAnimationFinished"

    },
    "MainTopWidget\0playVideo\0\0showSkin\0"
    "showMenu\0showMin\0closeWidget\0goExamine\0"
    "goMain\0setNums\0num\0examineClicked\0"
    "viewClicked\0returnMain\0returnAnimationFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainTopWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    0,   75,    2, 0x06 /* Public */,
       4,    0,   76,    2, 0x06 /* Public */,
       5,    0,   77,    2, 0x06 /* Public */,
       6,    0,   78,    2, 0x06 /* Public */,
       7,    0,   79,    2, 0x06 /* Public */,
       8,    0,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,   81,    2, 0x0a /* Public */,
      11,    0,   84,    2, 0x08 /* Private */,
      12,    0,   85,    2, 0x08 /* Private */,
      13,    0,   86,    2, 0x08 /* Private */,
      14,    0,   87,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainTopWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainTopWidget *_t = static_cast<MainTopWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->playVideo(); break;
        case 1: _t->showSkin(); break;
        case 2: _t->showMenu(); break;
        case 3: _t->showMin(); break;
        case 4: _t->closeWidget(); break;
        case 5: _t->goExamine(); break;
        case 6: _t->goMain(); break;
        case 7: _t->setNums((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->examineClicked(); break;
        case 9: _t->viewClicked(); break;
        case 10: _t->returnMain(); break;
        case 11: _t->returnAnimationFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainTopWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainTopWidget::playVideo)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MainTopWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainTopWidget::showSkin)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MainTopWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainTopWidget::showMenu)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MainTopWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainTopWidget::showMin)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MainTopWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainTopWidget::closeWidget)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MainTopWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainTopWidget::goExamine)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (MainTopWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainTopWidget::goMain)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject MainTopWidget::staticMetaObject = {
    { &BaseStyleWidget::staticMetaObject, qt_meta_stringdata_MainTopWidget.data,
      qt_meta_data_MainTopWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainTopWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainTopWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainTopWidget.stringdata0))
        return static_cast<void*>(const_cast< MainTopWidget*>(this));
    return BaseStyleWidget::qt_metacast(_clname);
}

int MainTopWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseStyleWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void MainTopWidget::playVideo()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainTopWidget::showSkin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MainTopWidget::showMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MainTopWidget::showMin()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MainTopWidget::closeWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MainTopWidget::goExamine()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MainTopWidget::goMain()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
