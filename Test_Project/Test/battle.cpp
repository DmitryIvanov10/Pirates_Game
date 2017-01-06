#include "battle.h"

Battle::Battle(QObject *parent)
{

}

Battle::Battle(Player *_player, Ship *_npc)
{
    timer->start(17*60);
    player_battle = true;
    qDebug() << "New player/npc battle.";

    ship1 = dynamic_cast<Ship *>(_player);
    ship2 = dynamic_cast<Ship *>(_npc);

    // show NPC parameters and goods
    qDebug() << "NPC model - " << _npc->get_model_name();
    qDebug() << "Health - " << _npc->get_health();
    qDebug() << "Crew - " << _npc->get_crew();
    qDebug() << "Cannons - " << _npc->get_cannons();
    qDebug() << "Ammo - " << _npc->get_ammo();
    qDebug() << "Maneuverability - " << _npc->get_maneuverability();

    foreach (Cargo * cargo, _npc->get_goods())
    {
        qDebug() << cargo->get_name() << ": " << cargo->get_amount();
    }

    morale_effect_1 = set_morale_effect(_player->get_morale());
    morale_effect_2 = set_morale_effect();

    connect(timer, SIGNAL(timeout()), this, SLOT(round()));
}

void Battle::run_away()
{
    qDebug() << "Ran away.";
    emit finish_battle();
}

void Battle::kill()
{
    qDebug() << "Killed NPC.";
    emit finish_battle();
}

float Battle::set_morale_effect()
{
    return 0.0025f * (rand() % 101) + 1.0f;
}

float Battle::set_morale_effect(short _morale)
{
    if (_morale > 0)
        return 1.0f + 0.005f * _morale;
    else
        return 1.0f;
}

void Battle::next_move(Ship *_ship1, Ship *_ship2)
{
    qDebug() << "New round";

    // set and normalize recharge speed (higher recharging speed - more fires in round)
    recharge_1 = morale_effect_1 * float(_ship1->get_crew()) /
            (_ship1->get_cannons() * _ship1->get_max_crew());
    recharge_2 = morale_effect_2 * float(_ship2->get_crew()) /
            (_ship2->get_cannons() * _ship2->get_max_crew());
    if (recharge_1 > recharge_2)
    {
        recharge_2 /= recharge_1;
        recharge_1 = 1.0f;
    } else
    {
        recharge_1 /= recharge_2;
        recharge_2 = 1.0f;
    }

    // calculate amount of cannonballs shot and reset amount of ammo
    round_ammo_shot_1 = short(float(_ship1->get_cannons())*recharge_1*0.5);
    round_ammo_shot_2 = short(float(_ship2->get_cannons())*recharge_2*0.5);
    if (_ship1->get_ammo() - round_ammo_shot_1 >= 0)
        _ship1->set_ammo(_ship1->get_ammo() - round_ammo_shot_1);
    else
    {
        round_ammo_shot_1 = _ship1->get_ammo();
        _ship1->set_ammo(0);
    }

    if (_ship2->get_ammo() - round_ammo_shot_2 >= 0)
        _ship2->set_ammo(_ship2->get_ammo() - round_ammo_shot_2);
    else
    {
        round_ammo_shot_2 = _ship2->get_ammo();
        _ship2->set_ammo(0);
    }

    // reset maneuverability
    _ship1->set_maneuverability(_ship1->get_health());
    _ship2->set_maneuverability(_ship2->get_health());

    // calculate damage
    round_damage_1 = short(3.0 * double(round_ammo_shot_1) * (1 - 0.5*_ship2->get_maneuverability()) *
                           0.01*(rand()%31 + 70.0) * morale_effect_1);
    round_damage_2 = short(3.0 * double(round_ammo_shot_2) * (1 - 0.5*_ship1->get_maneuverability()) *
                           0.01*(rand()%31 + 70.0) * morale_effect_2);

    // change health
    _ship1->set_health(_ship1->get_health() - round_damage_2);
    _ship2->set_health(_ship2->get_health() - round_damage_1);

    // change crew
    _ship1->set_crew(short(float(_ship1->get_crew()) *
                     (1 - 0.3f * float(round_damage_2)/_ship1->get_max_health())));
    _ship2->set_crew(short(float(_ship2->get_crew()) *
                     (1 - 0.3f * float(round_damage_1)/_ship2->get_max_health())));

    // change amount of cannons
    if (_ship1->get_cannons() >= 10)
        _ship1->set_cannons(_ship1->get_cannons() - rand() % 3);
    if (_ship2->get_cannons() >= 10)
        _ship2->set_cannons(_ship2->get_cannons() - rand() % 3);

    if (_ship2->get_health() < 0.2 * _ship2->get_max_health() || !_ship2->get_ammo())
    {
        timer->stop();
        kill();
        delete (_ship2);
    } else
    if (_ship1->get_health() < 0.2 * _ship1->get_max_health() || !_ship1->get_ammo())
    {
        timer->stop();
        run_away();
        delete (_ship2);
    }
}

void Battle::round()
{
    if (player_battle)
        next_move(ship1, ship2);
}


