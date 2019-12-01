/****************************************************************************
** Meta object code from reading C++ file 'keyboard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../keyboard/KeyBoard/KeyBoard/keyboard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'keyboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_KeyBoard_t {
    QByteArrayData data[13];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KeyBoard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KeyBoard_t qt_meta_stringdata_KeyBoard = {
    {
QT_MOC_LITERAL(0, 0, 8), // "KeyBoard"
QT_MOC_LITERAL(1, 9, 18), // "on_caps_Bt_clicked"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 15), // "slot_numClicked"
QT_MOC_LITERAL(4, 45, 16), // "QAbstractButton*"
QT_MOC_LITERAL(5, 62, 2), // "bt"
QT_MOC_LITERAL(6, 65, 15), // "slot_carClicked"
QT_MOC_LITERAL(7, 81, 19), // "slot_hanziBtClicked"
QT_MOC_LITERAL(8, 101, 19), // "on_zh_us_Bt_clicked"
QT_MOC_LITERAL(9, 121, 16), // "on_delBt_clicked"
QT_MOC_LITERAL(10, 138, 17), // "on_nextBt_clicked"
QT_MOC_LITERAL(11, 156, 17), // "on_prevBt_clicked"
QT_MOC_LITERAL(12, 174, 18) // "on_closeBt_clicked"

    },
    "KeyBoard\0on_caps_Bt_clicked\0\0"
    "slot_numClicked\0QAbstractButton*\0bt\0"
    "slot_carClicked\0slot_hanziBtClicked\0"
    "on_zh_us_Bt_clicked\0on_delBt_clicked\0"
    "on_nextBt_clicked\0on_prevBt_clicked\0"
    "on_closeBt_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KeyBoard[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    1,   60,    2, 0x08 /* Private */,
       6,    1,   63,    2, 0x08 /* Private */,
       7,    1,   66,    2, 0x08 /* Private */,
       8,    0,   69,    2, 0x08 /* Private */,
       9,    0,   70,    2, 0x08 /* Private */,
      10,    0,   71,    2, 0x08 /* Private */,
      11,    0,   72,    2, 0x08 /* Private */,
      12,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void KeyBoard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KeyBoard *_t = static_cast<KeyBoard *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_caps_Bt_clicked(); break;
        case 1: _t->slot_numClicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 2: _t->slot_carClicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 3: _t->slot_hanziBtClicked((*reinterpret_cast< QAbstractButton*(*)>(_a[1]))); break;
        case 4: _t->on_zh_us_Bt_clicked(); break;
        case 5: _t->on_delBt_clicked(); break;
        case 6: _t->on_nextBt_clicked(); break;
        case 7: _t->on_prevBt_clicked(); break;
        case 8: _t->on_closeBt_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject KeyBoard::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_KeyBoard.data,
      qt_meta_data_KeyBoard,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *KeyBoard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KeyBoard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_KeyBoard.stringdata0))
        return static_cast<void*>(const_cast< KeyBoard*>(this));
    return QDialog::qt_metacast(_clname);
}

int KeyBoard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
