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
    short round_time = 17*180;

    bool let_away = false;
    bool player_battle;

public:
    Battle(QObject *parent = 0);
    Battle(Player * _player, Ship * _npc);

    float set_morale_effect();
    float set_morale_effect(short _morale);

    void start_battle();

    void kill();
    void win_abordage();
    void run_away();
    void loose();

    void abordage();

    void next_move_sea();
    void next_move_abordage();

    void get_goods();
    void change_crew(short _amount);

    //void change_back_type(Ship * _ship);

signals:
    void change_player_morale(float value);
    void sink_abordage(short _battle_phase);
    void finish_battle();
    void lost(short _crew);
    void update_info();

public slots:
    void after_sea_battle(short _battle_phase);
    void round_on_sea();
    void round_of_abordage();
};

#endif // BATTLE_H
