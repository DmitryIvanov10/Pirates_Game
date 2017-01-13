/****************************************************************************
** Meta object code from reading C++ file 'game.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Test/game.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Game_t {
    QByteArrayData data[22];
    char stringdata0[255];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Game_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Game_t qt_meta_stringdata_Game = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Game"
QT_MOC_LITERAL(1, 5, 7), // "new_day"
QT_MOC_LITERAL(2, 13, 0), // ""
QT_MOC_LITERAL(3, 14, 13), // "sink_abordage"
QT_MOC_LITERAL(4, 28, 13), // "_battle_phase"
QT_MOC_LITERAL(5, 42, 16), // "show_battle_menu"
QT_MOC_LITERAL(6, 59, 13), // "show_npc_info"
QT_MOC_LITERAL(7, 73, 4), // "NPC*"
QT_MOC_LITERAL(8, 78, 5), // "_ship"
QT_MOC_LITERAL(9, 84, 13), // "hide_npc_info"
QT_MOC_LITERAL(10, 98, 10), // "count_days"
QT_MOC_LITERAL(11, 109, 13), // "update_states"
QT_MOC_LITERAL(12, 123, 11), // "center_view"
QT_MOC_LITERAL(13, 135, 19), // "start_player_battle"
QT_MOC_LITERAL(14, 155, 5), // "Ship*"
QT_MOC_LITERAL(15, 161, 17), // "end_player_battle"
QT_MOC_LITERAL(16, 179, 11), // "mouse_moved"
QT_MOC_LITERAL(17, 191, 13), // "mouse_pressed"
QT_MOC_LITERAL(18, 205, 11), // "reset_timer"
QT_MOC_LITERAL(19, 217, 10), // "delete_npc"
QT_MOC_LITERAL(20, 228, 11), // "esc_pressed"
QT_MOC_LITERAL(21, 240, 14) // "create_new_npc"

    },
    "Game\0new_day\0\0sink_abordage\0_battle_phase\0"
    "show_battle_menu\0show_npc_info\0NPC*\0"
    "_ship\0hide_npc_info\0count_days\0"
    "update_states\0center_view\0start_player_battle\0"
    "Ship*\0end_player_battle\0mouse_moved\0"
    "mouse_pressed\0reset_timer\0delete_npc\0"
    "esc_pressed\0create_new_npc"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Game[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    1,   95,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   98,    2, 0x0a /* Public */,
       6,    1,  101,    2, 0x0a /* Public */,
       9,    0,  104,    2, 0x0a /* Public */,
      10,    0,  105,    2, 0x0a /* Public */,
      11,    0,  106,    2, 0x0a /* Public */,
      12,    0,  107,    2, 0x0a /* Public */,
      13,    1,  108,    2, 0x0a /* Public */,
      15,    0,  111,    2, 0x0a /* Public */,
      16,    0,  112,    2, 0x0a /* Public */,
      17,    0,  113,    2, 0x0a /* Public */,
      18,    0,  114,    2, 0x0a /* Public */,
      19,    1,  115,    2, 0x0a /* Public */,
      20,    0,  118,    2, 0x0a /* Public */,
      21,    0,  119,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Short,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Short,    4,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Game *_t = static_cast<Game *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->new_day(); break;
        case 1: _t->sink_abordage((*reinterpret_cast< short(*)>(_a[1]))); break;
        case 2: _t->show_battle_menu((*reinterpret_cast< short(*)>(_a[1]))); break;
        case 3: _t->show_npc_info((*reinterpret_cast< NPC*(*)>(_a[1]))); break;
        case 4: _t->hide_npc_info(); break;
        case 5: _t->count_days(); break;
        case 6: _t->update_states(); break;
        case 7: _t->center_view(); break;
        case 8: _t->start_player_battle((*reinterpret_cast< Ship*(*)>(_a[1]))); break;
        case 9: _t->end_player_battle(); break;
        case 10: _t->mouse_moved(); break;
        case 11: _t->mouse_pressed(); break;
        case 12: _t->reset_timer(); break;
        case 13: _t->delete_npc((*reinterpret_cast< NPC*(*)>(_a[1]))); break;
        case 14: _t->esc_pressed(); break;
        case 15: _t->create_new_npc(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< NPC* >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Ship* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< NPC* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Game::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Game::new_day)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Game::*_t)(short );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Game::sink_abordage)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Game::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Game.data,
      qt_meta_data_Game,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Game::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Game.stringdata0))
        return static_cast<void*>(const_cast< Game*>(this));
    return QObject::qt_metacast(_clname);
}

int Game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void Game::new_day()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Game::sink_abordage(short _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
