/****************************************************************************
** Meta object code from reading C++ file 'vmdfile.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../vmdfile.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vmdfile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_vmdfile_t {
    QByteArrayData data[10];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vmdfile_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vmdfile_t qt_meta_stringdata_vmdfile = {
    {
QT_MOC_LITERAL(0, 0, 7), // "vmdfile"
QT_MOC_LITERAL(1, 8, 6), // "toMain"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 19), // "QStandardItemModel*"
QT_MOC_LITERAL(4, 36, 27), // "on_pushButton_close_clicked"
QT_MOC_LITERAL(5, 64, 30), // "on_pushButton_openfile_clicked"
QT_MOC_LITERAL(6, 95, 25), // "on_pushButton_del_clicked"
QT_MOC_LITERAL(7, 121, 28), // "on_pushButton_delAll_clicked"
QT_MOC_LITERAL(8, 150, 28), // "on_pushButton_change_clicked"
QT_MOC_LITERAL(9, 179, 26) // "on_pushButton_conf_clicked"

    },
    "vmdfile\0toMain\0\0QStandardItemModel*\0"
    "on_pushButton_close_clicked\0"
    "on_pushButton_openfile_clicked\0"
    "on_pushButton_del_clicked\0"
    "on_pushButton_delAll_clicked\0"
    "on_pushButton_change_clicked\0"
    "on_pushButton_conf_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vmdfile[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   52,    2, 0x08 /* Private */,
       5,    0,   53,    2, 0x08 /* Private */,
       6,    0,   54,    2, 0x08 /* Private */,
       7,    0,   55,    2, 0x08 /* Private */,
       8,    0,   56,    2, 0x08 /* Private */,
       9,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void vmdfile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<vmdfile *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->toMain((*reinterpret_cast< QStandardItemModel*(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_close_clicked(); break;
        case 2: _t->on_pushButton_openfile_clicked(); break;
        case 3: _t->on_pushButton_del_clicked(); break;
        case 4: _t->on_pushButton_delAll_clicked(); break;
        case 5: _t->on_pushButton_change_clicked(); break;
        case 6: _t->on_pushButton_conf_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
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
            using _t = void (vmdfile::*)(QStandardItemModel * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vmdfile::toMain)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject vmdfile::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_vmdfile.data,
    qt_meta_data_vmdfile,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *vmdfile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vmdfile::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vmdfile.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int vmdfile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void vmdfile::toMain(QStandardItemModel * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE