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
#include <npc.h>
#include <pirate.h>
#include <player.h>

class Battle: public QObject
{
    Q_OBJECT

    QTimer * timer = new QTimer();
    float recharge_1;
    float recharge_2;
    float morale_effect_1;
    float morale_effect_2;
    short round_ammo_shot_1;
    short round_ammo_shot_2;
    short round_damage_1;
    short round_damage_2;

public:
    Battle(QObject *parent = 0);
    Battle(Player * _player, NPC * _npc);

    void start_battle(Player * _player, NPC * _npc);
    void finish_battle(Player * _player, NPC * _npc);
    void abordage(Player * _player, NPC * _npc);
    void kill(Player * _player, NPC * _npc);
    float set_morale_effect();
    float set_morale_effect(short _morale);

signals:

public slots:
    void next_move(Ship * _player, Ship * _npc);
};

#endif // BATTLE_H
