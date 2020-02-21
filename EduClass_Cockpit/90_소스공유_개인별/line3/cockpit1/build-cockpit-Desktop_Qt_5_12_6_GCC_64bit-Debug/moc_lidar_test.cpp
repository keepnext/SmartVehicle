/****************************************************************************
** Meta object code from reading C++ file 'lidar_test.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../cockpit/lidar_test.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lidar_test.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lidar_test_t {
    QByteArrayData data[7];
    char stringdata0[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lidar_test_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lidar_test_t qt_meta_stringdata_lidar_test = {
    {
QT_MOC_LITERAL(0, 0, 10), // "lidar_test"
QT_MOC_LITERAL(1, 11, 7), // "recvYaw"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 14), // "connetbtn_push"
QT_MOC_LITERAL(4, 35, 13), // "tcp_connected"
QT_MOC_LITERAL(5, 49, 15), // "tcp_recved_data"
QT_MOC_LITERAL(6, 65, 16) // "tcp_disconnected"

    },
    "lidar_test\0recvYaw\0\0connetbtn_push\0"
    "tcp_connected\0tcp_recved_data\0"
    "tcp_disconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lidar_test[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       3,    0,   42,    2, 0x08 /* Private */,
       4,    0,   43,    2, 0x08 /* Private */,
       5,    0,   44,    2, 0x08 /* Private */,
       6,    0,   45,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void lidar_test::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<lidar_test *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->recvYaw((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->connetbtn_push(); break;
        case 2: _t->tcp_connected(); break;
        case 3: _t->tcp_recved_data(); break;
        case 4: _t->tcp_disconnected(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lidar_test::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_lidar_test.data,
    qt_meta_data_lidar_test,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lidar_test::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lidar_test::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lidar_test.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int lidar_test::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
