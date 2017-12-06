/****************************************************************************
** Meta object code from reading C++ file 'modelconversas.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../WhatsProg_cliente/modelconversas.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modelconversas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ModelConversas_t {
    QByteArrayData data[5];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModelConversas_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModelConversas_t qt_meta_stringdata_ModelConversas = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ModelConversas"
QT_MOC_LITERAL(1, 15, 21), // "slotAtualizaConversas"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 26), // "slotAtualizaNumMsgConversa"
QT_MOC_LITERAL(4, 65, 1) // "I"

    },
    "ModelConversas\0slotAtualizaConversas\0"
    "\0slotAtualizaNumMsgConversa\0I"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModelConversas[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    1,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,    4,

       0        // eod
};

void ModelConversas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModelConversas *_t = static_cast<ModelConversas *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotAtualizaConversas(); break;
        case 1: _t->slotAtualizaNumMsgConversa((*reinterpret_cast< uint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ModelConversas::staticMetaObject = {
    { &QAbstractTableModel::staticMetaObject, qt_meta_stringdata_ModelConversas.data,
      qt_meta_data_ModelConversas,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ModelConversas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModelConversas::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ModelConversas.stringdata0))
        return static_cast<void*>(this);
    return QAbstractTableModel::qt_metacast(_clname);
}

int ModelConversas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
