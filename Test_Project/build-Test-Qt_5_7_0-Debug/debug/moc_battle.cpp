/****************************************************************************
** Meta object code from reading C++ file 'battle.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Test/battle.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'battle.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Battle_t {
    QByteArrayData data[7];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Battle_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Battle_t qt_meta_stringdata_Battle = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Battle"
QT_MOC_LITERAL(1, 7, 20), // "change_player_morale"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 5), // "value"
QT_MOC_LITERAL(4, 35, 13), // "finish_battle"
QT_MOC_LITERAL(5, 49, 12), // "round_on_sea"
QT_MOC_LITERAL(6, 62, 17) // "round_of_abordage"

    },
    "Battle\0change_player_morale\0\0value\0"
    "finish_battle\0round_on_sea\0round_of_abordage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Battle[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    0,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   38,    2, 0x0a /* Public */,
       6,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Battle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Battle *_t = static_cast<Battle *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->change_player_morale((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->finish_battle(); break;
        case 2: _t->round_on_sea(); break;
        case 3: _t->round_of_abordage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Battle::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Battle::change_player_morale)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Battle::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Battle::finish_battle)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Battle::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Battle.data,
      qt_meta_data_Battle,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Battle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Battle::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Battle.stringdata0))
        return static_cast<void*>(const_cast< Battle*>(this));
    return QObject::qt_metacast(_clname);
}

int Battle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Battle::change_player_morale(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Battle::finish_battle()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
