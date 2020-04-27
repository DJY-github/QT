/****************************************************************************
** Meta object code from reading C++ file 'scanbuttonwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Qt360-10.0/src/safe/common/scanbuttonwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scanbuttonwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScanButtonWidget_t {
    QByteArrayData data[8];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScanButtonWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScanButtonWidget_t qt_meta_stringdata_ScanButtonWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ScanButtonWidget"
QT_MOC_LITERAL(1, 17, 13), // "buttonClicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 7), // "animPix"
QT_MOC_LITERAL(4, 40, 7), // "animNum"
QT_MOC_LITERAL(5, 48, 9), // "normalPix"
QT_MOC_LITERAL(6, 58, 9), // "normalNum"
QT_MOC_LITERAL(7, 68, 4) // "text"

    },
    "ScanButtonWidget\0buttonClicked\0\0animPix\0"
    "animNum\0normalPix\0normalNum\0text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScanButtonWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       5,   20, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // properties: name, type, flags
       3, QMetaType::QString, 0x00095103,
       4, QMetaType::Int, 0x00095103,
       5, QMetaType::QString, 0x00095103,
       6, QMetaType::Int, 0x00095103,
       7, QMetaType::QString, 0x00095103,

       0        // eod
};

void ScanButtonWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScanButtonWidget *_t = static_cast<ScanButtonWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->buttonClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ScanButtonWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScanButtonWidget::buttonClicked)) {
                *result = 0;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        ScanButtonWidget *_t = static_cast<ScanButtonWidget *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->animPix(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->animNum(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->normalPix(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->normalNum(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->text(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        ScanButtonWidget *_t = static_cast<ScanButtonWidget *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAnimPix(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setAnimNum(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setNormalPix(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setNormalNum(*reinterpret_cast< int*>(_v)); break;
        case 4: _t->setText(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_a);
}

const QMetaObject ScanButtonWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ScanButtonWidget.data,
      qt_meta_data_ScanButtonWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ScanButtonWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScanButtonWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScanButtonWidget.stringdata0))
        return static_cast<void*>(const_cast< ScanButtonWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ScanButtonWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ScanButtonWidget::buttonClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
