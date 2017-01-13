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
    QByteArrayData data[13];
    char stringdata0[148];
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
QT_MOC_LITERAL(4, 35, 13), // "sink_abordage"
QT_MOC_LITERAL(5, 49, 13), // "_battle_phase"
QT_MOC_LITERAL(6, 63, 13), // "finish_battle"
QT_MOC_LITERAL(7, 77, 4), // "lost"
QT_MOC_LITERAL(8, 82, 5), // "_crew"
QT_MOC_LITERAL(9, 88, 11), // "update_info"
QT_MOC_LITERAL(10, 100, 16), // "after_sea_battle"
QT_MOC_LITERAL(11, 117, 12), // "round_on_sea"
QT_MOC_LITERAL(12, 130, 17) // "round_of_abordage"

    },
    "Battle\0change_player_morale\0\0value\0"
    "sink_abordage\0_battle_phase\0finish_battle\0"
    "lost\0_crew\0update_info\0after_sea_battle\0"
    "round_on_sea\0round_of_abordage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Battle[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       6,    0,   60,    2, 0x06 /* Public */,
       7,    1,   61,    2, 0x06 /* Public */,
       9,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   65,    2, 0x0a /* Public */,
      11,    0,   68,    2, 0x0a /* Public */,
      12,    0,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    3,
    QMetaType::Void, QMetaType::Short,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Short,    8,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Short,    5,
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
        case 1: _t->sink_abordage((*reinterpret_cast< short(*)>(_a[1]))); break;
        case 2: _t->finish_battle(); break;
        case 3: _t->lost((*reinterpret_cast< short(*)>(_a[1]))); break;
        case 4: _t->update_info(); break;
        case 5: _t->after_sea_battle((*reinterpret_cast< short(*)>(_a[1]))); break;
        case 6: _t->round_on_sea(); break;
        case 7: _t->round_of_abordage(); break;
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
            typedef void (Battle::*_t)(short );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Battle::sink_abordage)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Battle::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Battle::finish_battle)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Battle::*_t)(short );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Battle::lost)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Battle::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Battle::update_info)) {
                *result = 4;
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
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
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
void Battle::sink_abordage(short _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Battle::finish_battle()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void Battle::lost(short _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Battle::update_info()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
