/****************************************************************************
** Meta object code from reading C++ file 'ProcessModelWithQt3D.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.15)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "ProcessModelWithQt3D.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ProcessModelWithQt3D.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.15. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ProcessModelWithQt3D_t {
    QByteArrayData data[7];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ProcessModelWithQt3D_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ProcessModelWithQt3D_t qt_meta_stringdata_ProcessModelWithQt3D = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ProcessModelWithQt3D"
QT_MOC_LITERAL(1, 21, 25), // "on_load3DModelBtn_clicked"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 40), // "on_directionComboBox_currentI..."
QT_MOC_LITERAL(4, 89, 5), // "index"
QT_MOC_LITERAL(5, 95, 26), // "on_createGrayImage_clicked"
QT_MOC_LITERAL(6, 122, 24) // "on_saveGrayImage_clicked"

    },
    "ProcessModelWithQt3D\0on_load3DModelBtn_clicked\0"
    "\0on_directionComboBox_currentIndexChanged\0"
    "index\0on_createGrayImage_clicked\0"
    "on_saveGrayImage_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ProcessModelWithQt3D[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    1,   35,    2, 0x08 /* Private */,
       5,    0,   38,    2, 0x08 /* Private */,
       6,    0,   39,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ProcessModelWithQt3D::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ProcessModelWithQt3D *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_load3DModelBtn_clicked(); break;
        case 1: _t->on_directionComboBox_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_createGrayImage_clicked(); break;
        case 3: _t->on_saveGrayImage_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ProcessModelWithQt3D::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ProcessModelWithQt3D.data,
    qt_meta_data_ProcessModelWithQt3D,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ProcessModelWithQt3D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ProcessModelWithQt3D::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ProcessModelWithQt3D.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ProcessModelWithQt3D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
