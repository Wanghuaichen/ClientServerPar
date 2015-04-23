/****************************************************************************
** Meta object code from reading C++ file 'psserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../psserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'psserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PsServer_t {
    QByteArrayData data[11];
    char stringdata[96];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PsServer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PsServer_t qt_meta_stringdata_PsServer = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PsServer"
QT_MOC_LITERAL(1, 9, 11), // "addLogToGui"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 6), // "string"
QT_MOC_LITERAL(4, 29, 5), // "color"
QT_MOC_LITERAL(5, 35, 16), // "onMessageFromGui"
QT_MOC_LITERAL(6, 52, 7), // "message"
QT_MOC_LITERAL(7, 60, 5), // "users"
QT_MOC_LITERAL(8, 66, 12), // "onRemoveUser"
QT_MOC_LITERAL(9, 79, 9), // "PsClient*"
QT_MOC_LITERAL(10, 89, 6) // "client"

    },
    "PsServer\0addLogToGui\0\0string\0color\0"
    "onMessageFromGui\0message\0users\0"
    "onRemoveUser\0PsClient*\0client"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PsServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   34,    2, 0x0a /* Public */,
       8,    1,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QColor,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList,    6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void PsServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PsServer *_t = static_cast<PsServer *>(_o);
        switch (_id) {
        case 0: _t->addLogToGui((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QColor(*)>(_a[2]))); break;
        case 1: _t->onMessageFromGui((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2]))); break;
        case 2: _t->onRemoveUser((*reinterpret_cast< PsClient*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PsClient* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PsServer::*_t)(QString , QColor );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PsServer::addLogToGui)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject PsServer::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_PsServer.data,
      qt_meta_data_PsServer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PsServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PsServer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PsServer.stringdata))
        return static_cast<void*>(const_cast< PsServer*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int PsServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void PsServer::addLogToGui(QString _t1, QColor _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
