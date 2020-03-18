/****************************************************************************
** Meta object code from reading C++ file 'frmlunarcalendarwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../lunarcalendarwidget/frmlunarcalendarwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frmlunarcalendarwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_frmLunarCalendarWidget_t {
    QByteArrayData data[9];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_frmLunarCalendarWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_frmLunarCalendarWidget_t qt_meta_stringdata_frmLunarCalendarWidget = {
    {
QT_MOC_LITERAL(0, 0, 22), // "frmLunarCalendarWidget"
QT_MOC_LITERAL(1, 23, 8), // "initForm"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 40), // "on_cboxCalendarStyle_currentI..."
QT_MOC_LITERAL(4, 74, 5), // "index"
QT_MOC_LITERAL(5, 80, 37), // "on_cboxSelectType_currentInde..."
QT_MOC_LITERAL(6, 118, 41), // "on_cboxWeekNameFormat_current..."
QT_MOC_LITERAL(7, 160, 27), // "on_ckShowLunar_stateChanged"
QT_MOC_LITERAL(8, 188, 4) // "arg1"

    },
    "frmLunarCalendarWidget\0initForm\0\0"
    "on_cboxCalendarStyle_currentIndexChanged\0"
    "index\0on_cboxSelectType_currentIndexChanged\0"
    "on_cboxWeekNameFormat_currentIndexChanged\0"
    "on_ckShowLunar_stateChanged\0arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_frmLunarCalendarWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    1,   40,    2, 0x08 /* Private */,
       5,    1,   43,    2, 0x08 /* Private */,
       6,    1,   46,    2, 0x08 /* Private */,
       7,    1,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void frmLunarCalendarWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        frmLunarCalendarWidget *_t = static_cast<frmLunarCalendarWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->initForm(); break;
        case 1: _t->on_cboxCalendarStyle_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_cboxSelectType_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_cboxWeekNameFormat_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_ckShowLunar_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject frmLunarCalendarWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_frmLunarCalendarWidget.data,
      qt_meta_data_frmLunarCalendarWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *frmLunarCalendarWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *frmLunarCalendarWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_frmLunarCalendarWidget.stringdata0))
        return static_cast<void*>(const_cast< frmLunarCalendarWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int frmLunarCalendarWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
