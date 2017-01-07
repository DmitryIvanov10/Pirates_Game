#include "battle.h"

Battle::Battle(QObject *parent)
{

}

Battle::Battle(Player *_player, Ship *_npc)
{
    timer1->start(17*60);
    player_battle = true;

    qDebug() << "";
    qDebug() << "New player/npc battle.";

    ship1 = dynamic_cast<Ship *>(_player);
    ship2 = dynamic_cast<Ship *>(_npc);

    // show NPC parameters and goods
    qDebug() << "";
    qDebug() << "NPC model - " << _npc->get_model_name();
    qDebug() << "Health - " << _npc->get_health();
    qDebug() << "Crew - " << _npc->get_crew();
    qDebug() << "Cannons - " << _npc->get_cannons();
    qDebug() << "Ammo - " << _npc->get_ammo();
    qDebug() << "Maneuverability - " << _npc->get_maneuverability();
    qDebug() << "";

    foreach (Cargo * cargo, _npc->get_goods())
    {
        qDebug() << cargo->get_name() << ": " << cargo->get_amount();
    }

    morale_effect_1 = set_morale_effect(_player->get_morale());
    morale_effect_2 = set_morale_effect();

    qDebug() << "";
    qDebug() << "Player morale effect - " << morale_effect_1;
    qDebug() << "NPC morale effect - " << morale_effect_2;
    qDebug() << "";

    connect(timer1, SIGNAL(timeout()), this, SLOT(round_on_sea()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(round_of_abordage()));
}

void Battle::run_away(Ship * _ship)
{
    change_back_type(_ship);
    qDebug() << "Ran away.";
    /*if (typeid( * _ship) == typeid(NPC))
        qDebug() << "Delete NPC.";
    if (typeid( * _ship) == typeid(Ship))
        qDebug() << "Delete Ship.";*/
    delete _ship;
    emit finish_battle();
}

void Battle::loose(Ship * _ship)
{
    change_back_type(_ship);
    qDebug() << "Lost abordage";
    /*if (typeid( * _ship) == typeid(NPC))
        qDebug() << "Delete NPC.";
    if (typeid( * _ship) == typeid(Ship))
        qDebug() << "Delete Ship.";*/
    delete _ship;
    emit finish_battle();
}

void Battle::abordage(Ship *_ship1, Ship *_ship2)
{
    qDebug() << "";
    qDebug() << "Abordage!";
    qDebug() << "Player crew - " << _ship1->get_crew();
    qDebug() << "Player morale effect -" << morale_effect_1;
    qDebug() << "NPC crew - " << _ship2->get_crew();
    qDebug() << "NPC morale effect -" << morale_effect_2;

    connect(timer2, SIGNAL(timeout()), this, SLOT(round_of_abordage()));
}

void Battle::kill(Ship * _ship)
{
    change_back_type(_ship);
    qDebug() << "Killed NPC.";
    /*if (typeid( * _ship) == typeid(NPC))
        qDebug() << "Delete NPC.";
    if (typeid( * _ship) == typeid(Ship))
        qDebug() << "Delete Ship.";*/
    delete _ship;
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

void Battle::next_move_sea(Ship *_ship1, Ship *_ship2)
{
    if (timer1->isActive())
    {
        qDebug() << "";
        qDebug() << "New round on sea.";

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
                               0.01f*(rand()%31 + 70.0) * morale_effect_1);
        round_damage_2 = short(3.0 * double(round_ammo_shot_2) * (1 - 0.5*_ship1->get_maneuverability()) *
                               0.01f*(rand()%31 + 70.0) * morale_effect_2);

        qDebug() << "";
        qDebug() << "Player damage - " << round_damage_1;
        qDebug() << "NPC damage - " << round_damage_2;
        qDebug() << "";

        // change health
        if (_ship1->get_health() > round_damage_2 + 5)
            _ship1->set_health(_ship1->get_health() - round_damage_2);
        else
        {
            timer1->stop();
            loose(_ship2);
            return;
        }

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

        qDebug() << "";

        qDebug() << "Player health - " << _ship1->get_health();
        qDebug() << "Player crew - " << _ship1->get_crew();
        qDebug() << "Player cannons - " << _ship1->get_cannons();
        qDebug() << "Player ammo - " << _ship1->get_ammo();
        qDebug() << "Player maneuverability - " << _ship1->get_maneuverability();
        qDebug() << "";

        qDebug() << "NPC health - " << _ship2->get_health();
        qDebug() << "NPC crew - " << _ship2->get_crew();
        qDebug() << "NPC cannons - " << _ship2->get_cannons();
        qDebug() << "NPC ammo - " << _ship2->get_ammo();
        qDebug() << "NPC maneuverability - " << _ship2->get_maneuverability();
        qDebug() << "";

        if (_ship2->get_health() <= 0)
        {
            timer1->stop();
            kill(_ship2);
            return;
        } else
        if (_ship2->get_health() < 0.2 * _ship2->get_max_health() || !_ship2->get_ammo())
        {
            timer1->stop();
            timer2->start(17*10);
            abordage(_ship1, _ship2);
        } else
        if (_ship1->get_health() < 0.2 * _ship1->get_max_health() || !_ship1->get_ammo())
        {
            timer1->stop();
            run_away(_ship2);
            return;
        }
    }
}

void Battle::next_move_abordage(Ship *_ship1, Ship *_ship2)
{
    if (timer2->isActive())
    {
        qDebug() << "";
        qDebug() << "New round of abordage.";
        qDebug() << "";

        qDebug() << "Player crew - " << _ship1->get_crew();
        qDebug() << "NPC crew - " << _ship2->get_crew();

        // count and apply round damage
        round_damage_1 = short(0.2f * morale_effect_1 * float(_ship1->get_crew()) *
                               0.01f * (rand()%31 + 70.0));
        round_damage_2 = short(0.2f * morale_effect_2 * float(_ship2->get_crew()) *
                               0.01f * (rand()%31 + 70.0));

        qDebug() << "Player damage - " << round_damage_1;
        qDebug() << "NPC damage - " << round_damage_2;

        if (_ship1->get_crew() > 10 + round_damage_2)
            _ship1->set_crew(_ship1->get_crew() - round_damage_2);
        else
        {
            timer2->stop();
            loose(_ship2);
            return;
        }
        if (_ship2->get_crew() > round_damage_1)
            _ship2->set_crew(_ship2->get_crew() - round_damage_1);
        else
        {
            _ship2->set_crew(10);
            timer2->stop();
            kill(_ship2);
            return;
        }

        if (_ship2->get_crew() < 0.2 * _ship2->get_max_crew())
        {
            timer2->stop();
            kill(_ship2);
            return;
        };
    }
}

void Battle::change_back_type(Ship *_ship)
{
    if (dynamic_cast<NPC *>(_ship) != 0)
        _ship = dynamic_cast<NPC *>(_ship);
    if (dynamic_cast<Pirate *>(_ship) != 0)
        _ship = dynamic_cast<Pirate *>(_ship);
}

void Battle::round_on_sea()
{
    if (player_battle)
        next_move_sea(ship1, ship2);
}

void Battle::round_of_abordage()
{
    next_move_abordage(ship1, ship2);
}


