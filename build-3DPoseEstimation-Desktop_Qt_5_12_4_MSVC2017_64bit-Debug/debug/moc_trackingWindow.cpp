/****************************************************************************
** Meta object code from reading C++ file 'trackingWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../3DPoseEstimation-QT/trackingWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trackingWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TrackingWindow_t {
    QByteArrayData data[16];
    char stringdata0[306];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TrackingWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TrackingWindow_t qt_meta_stringdata_TrackingWindow = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TrackingWindow"
QT_MOC_LITERAL(1, 15, 8), // "mySignal"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "mySignalParm"
QT_MOC_LITERAL(4, 38, 23), // "on_pushButton_6_clicked"
QT_MOC_LITERAL(5, 62, 23), // "on_pushButton_7_clicked"
QT_MOC_LITERAL(6, 86, 25), // "on_pushButton_add_clicked"
QT_MOC_LITERAL(7, 112, 25), // "on_pushButton_del_clicked"
QT_MOC_LITERAL(8, 138, 28), // "on_pushButton_delAll_clicked"
QT_MOC_LITERAL(9, 167, 25), // "on_pushButton_VMD_clicked"
QT_MOC_LITERAL(10, 193, 25), // "on_pushButton_FBX_clicked"
QT_MOC_LITERAL(11, 219, 24), // "on_pushButton_VF_clicked"
QT_MOC_LITERAL(12, 244, 26), // "on_pushButton_path_clicked"
QT_MOC_LITERAL(13, 271, 7), // "fromVMD"
QT_MOC_LITERAL(14, 279, 19), // "QStandardItemModel*"
QT_MOC_LITERAL(15, 299, 6) // "vmodel"

    },
    "TrackingWindow\0mySignal\0\0mySignalParm\0"
    "on_pushButton_6_clicked\0on_pushButton_7_clicked\0"
    "on_pushButton_add_clicked\0"
    "on_pushButton_del_clicked\0"
    "on_pushButton_delAll_clicked\0"
    "on_pushButton_VMD_clicked\0"
    "on_pushButton_FBX_clicked\0"
    "on_pushButton_VF_clicked\0"
    "on_pushButton_path_clicked\0fromVMD\0"
    "QStandardItemModel*\0vmodel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TrackingWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    2,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   80,    2, 0x08 /* Private */,
       5,    0,   81,    2, 0x08 /* Private */,
       6,    0,   82,    2, 0x08 /* Private */,
       7,    0,   83,    2, 0x08 /* Private */,
       8,    0,   84,    2, 0x08 /* Private */,
       9,    0,   85,    2, 0x08 /* Private */,
      10,    0,   86,    2, 0x08 /* Private */,
      11,    0,   87,    2, 0x08 /* Private */,
      12,    0,   88,    2, 0x08 /* Private */,
      13,    1,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,

       0        // eod
};

void TrackingWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TrackingWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mySignal(); break;
        case 1: _t->mySignalParm((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->on_pushButton_6_clicked(); break;
        case 3: _t->on_pushButton_7_clicked(); break;
        case 4: _t->on_pushButton_add_clicked(); break;
        case 5: _t->on_pushButton_del_clicked(); break;
        case 6: _t->on_pushButton_delAll_clicked(); break;
        case 7: _t->on_pushButton_VMD_clicked(); break;
        case 8: _t->on_pushButton_FBX_clicked(); break;
        case 9: _t->on_pushButton_VF_clicked(); break;
        case 10: _t->on_pushButton_path_clicked(); break;
        case 11: _t->fromVMD((*reinterpret_cast< QStandardItemModel*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QStandardItemModel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TrackingWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackingWindow::mySignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TrackingWindow::*)(int , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackingWindow::mySignalParm)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TrackingWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_TrackingWindow.data,
    qt_meta_data_TrackingWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TrackingWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrackingWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TrackingWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int TrackingWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void TrackingWindow::mySignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void TrackingWindow::mySignalParm(int _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
