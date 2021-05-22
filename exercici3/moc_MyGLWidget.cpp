/****************************************************************************
** Meta object code from reading C++ file 'MyGLWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "MyGLWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyGLWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyGLWidget_t {
    QByteArrayData data[8];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyGLWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyGLWidget_t qt_meta_stringdata_MyGLWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MyGLWidget"
QT_MOC_LITERAL(1, 11, 6), // "allOff"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 5), // "oneOn"
QT_MOC_LITERAL(4, 25, 5), // "twoOn"
QT_MOC_LITERAL(5, 31, 5), // "allOn"
QT_MOC_LITERAL(6, 37, 10), // "reactorSig"
QT_MOC_LITERAL(7, 48, 7) // "reactor"

    },
    "MyGLWidget\0allOff\0\0oneOn\0twoOn\0allOn\0"
    "reactorSig\0reactor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyGLWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       3,    1,   67,    2, 0x06 /* Public */,
       4,    1,   70,    2, 0x06 /* Public */,
       5,    1,   73,    2, 0x06 /* Public */,
       6,    1,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x0a /* Public */,
       4,    0,   81,    2, 0x0a /* Public */,
       5,    0,   82,    2, 0x0a /* Public */,
       7,    1,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void MyGLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyGLWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->allOff((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->oneOn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->twoOn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->allOn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->reactorSig((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->allOff(); break;
        case 6: _t->oneOn(); break;
        case 7: _t->twoOn(); break;
        case 8: _t->allOn(); break;
        case 9: _t->reactor((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyGLWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::allOff)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyGLWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::oneOn)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyGLWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::twoOn)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MyGLWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::allOn)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MyGLWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGLWidget::reactorSig)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyGLWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_meta_stringdata_MyGLWidget.data,
    qt_meta_data_MyGLWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyGLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyGLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyGLWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions_3_3_Core"))
        return static_cast< QOpenGLFunctions_3_3_Core*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int MyGLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void MyGLWidget::allOff(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyGLWidget::oneOn(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyGLWidget::twoOn(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MyGLWidget::allOn(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MyGLWidget::reactorSig(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
