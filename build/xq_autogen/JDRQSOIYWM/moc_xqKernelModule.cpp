/****************************************************************************
** Meta object code from reading C++ file 'xqKernelModule.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/xq/xqKernelModule.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xqKernelModule.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_xqKernelModule_t {
    const uint offsetsAndSize[18];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_xqKernelModule_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_xqKernelModule_t qt_meta_stringdata_xqKernelModule = {
    {
QT_MOC_LITERAL(0, 14), // "xqKernelModule"
QT_MOC_LITERAL(15, 13), // "kernelStarted"
QT_MOC_LITERAL(29, 0), // ""
QT_MOC_LITERAL(30, 19), // "kernelStopRequested"
QT_MOC_LITERAL(50, 11), // "startKernel"
QT_MOC_LITERAL(62, 14), // "connectionFile"
QT_MOC_LITERAL(77, 10), // "stopKernel"
QT_MOC_LITERAL(88, 18), // "setPollIntervalSec"
QT_MOC_LITERAL(107, 11) // "intervalSec"

    },
    "xqKernelModule\0kernelStarted\0\0"
    "kernelStopRequested\0startKernel\0"
    "connectionFile\0stopKernel\0setPollIntervalSec\0"
    "intervalSec"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_xqKernelModule[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    0 /* Public */,
       3,    0,   45,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    1,   46,    2, 0x0a,    2 /* Public */,
       6,    0,   49,    2, 0x0a,    4 /* Public */,
       7,    1,   50,    2, 0x0a,    5 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    8,

       0        // eod
};

void xqKernelModule::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<xqKernelModule *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->kernelStarted(); break;
        case 1: _t->kernelStopRequested(); break;
        case 2: _t->startKernel((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->stopKernel(); break;
        case 4: _t->setPollIntervalSec((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (xqKernelModule::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&xqKernelModule::kernelStarted)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (xqKernelModule::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&xqKernelModule::kernelStopRequested)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject xqKernelModule::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_xqKernelModule.offsetsAndSize,
    qt_meta_data_xqKernelModule,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_xqKernelModule_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>


>,
    nullptr
} };


const QMetaObject *xqKernelModule::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *xqKernelModule::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_xqKernelModule.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int xqKernelModule::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void xqKernelModule::kernelStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void xqKernelModule::kernelStopRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
