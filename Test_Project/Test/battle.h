#ifndef BATTLE_H
#define BATTLE_H

//biblioteki
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <math.h>
#include <cstdlib>
#include <time.h>

//pliki
#include "npc.h"
#include "pirate.h"
#include "player.h"

class Battle: public QObject
{
    Q_OBJECT

    QTimer * timer1 = new QTimer();
    QTimer * timer2 = new QTimer();

    Ship * ship1;
    Ship * ship2;

    float recharge_1;
    float recharge_2;
    float morale_effect_1;
    float morale_effect_2;
    short round_ammo_shot_1;
    short round_ammo_shot_2;
    short round_damage_1;
    short round_damage_2;

    bool player_battle;

public:
    Battle(QObject *parent = 0);
    Battle(Player * _player, Ship * _npc);

    void start_battle();
    void run_away(Ship * _ship);
    void loose(Ship * _ship);
    void abordage(Ship *_ship1, Ship *_ship2);
    void kill(Ship * _ship);
    float set_morale_effect();
    float set_morale_effect(short _morale);

    void next_move_sea(Ship *_ship1, Ship *_ship2);
    void next_move_abordage(Ship *_ship1, Ship *_ship2);

    void change_back_type(Ship * _ship);

signals:
    void finish_battle();

public slots:
    void round_on_sea();
    void round_of_abordage();
};

#endif // BATTLE_H
