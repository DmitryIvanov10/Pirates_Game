#include "battle.h"

Battle::Battle(QObject *parent)
{

}

Battle::Battle(Player *_player, Ship *_npc)
{
    timer1->start(round_time);
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
    connect(this, SIGNAL(change_player_morale(float)), _player, SLOT(set_days_off_harbor_morale(float)));
}

void Battle::kill()
{
    //change_back_type(ship2);
    qDebug() << "Sank NPC.";
    foreach (Cargo * cargo, ship2->get_goods())
    {
        cargo->change_amount(-short(float(cargo->get_amount()) *
                                   0.01f*(rand()%50 + 25.0)));
        qDebug() << cargo->get_name() << " - " << cargo->get_amount();
    }
    get_goods();

    morale_effect_1 += 0.075f;
    if (morale_effect_1 > 1.5)
        morale_effect_1 = 1.5;

    emit finish_battle();
}

void Battle::win_abordage()
{
    //change_back_type(ship2);
    qDebug() << "Won abordage!";
    get_goods();

    ship1->set_ammo(ship1->get_ammo() + ship2->get_ammo());
    ship2->set_ammo(0);

    morale_effect_1 += 0.125f;
    if (morale_effect_1 > 1.5)
        morale_effect_1 = 1.5;

    morale_effect_2 = 0;

    emit finish_battle();
}

void Battle::run_away()
{
    //change_back_type(ship2);
    qDebug() << "Ran away.";
    emit finish_battle();
}

void Battle::loose()
{
    //change_back_type(ship2);
    qDebug() << "Lost abordage or got drowned";
    emit lost(ship1->get_crew());
    emit finish_battle();
}

void Battle::abordage()
{
    qDebug() << "";
    qDebug() << "Abordage!";
    qDebug() << "Player crew - " << ship1->get_crew();
    qDebug() << "Player morale effect -" << morale_effect_1;
    qDebug() << "NPC crew - " << ship2->get_crew();
    qDebug() << "NPC morale effect -" << morale_effect_2;

    connect(timer2, SIGNAL(timeout()), this, SLOT(round_of_abordage()));
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

void Battle::next_move_sea()
{
    if (timer1->isActive())
    {
        qDebug() << "";
        qDebug() << "New round on sea.";

        // set and normalize recharge speed (higher recharging speed - more fires in round)
        recharge_1 = morale_effect_1 * float(ship1->get_crew()) /
                (ship1->get_cannons() * ship1->get_max_crew());
        recharge_2 = morale_effect_2 * float(ship2->get_crew()) /
                (ship2->get_cannons() * ship2->get_max_crew());
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
        round_ammo_shot_1 = short(float(ship1->get_cannons())*recharge_1*0.5);
        round_ammo_shot_2 = short(float(ship2->get_cannons())*recharge_2*0.5);
        if (ship1->get_ammo() - round_ammo_shot_1 >= 0)
            ship1->set_ammo(ship1->get_ammo() - round_ammo_shot_1);
        else
        {
            round_ammo_shot_1 = ship1->get_ammo();
            ship1->set_ammo(0);
        }

        if (ship2->get_ammo() - round_ammo_shot_2 >= 0)
            ship2->set_ammo(ship2->get_ammo() - round_ammo_shot_2);
        else
        {
            round_ammo_shot_2 = ship2->get_ammo();
            ship2->set_ammo(0);
        }

        // reset maneuverability
        ship1->set_maneuverability(ship1->get_health());
        ship2->set_maneuverability(ship2->get_health());

        // calculate damage
        round_damage_1 = short(3.0 * double(round_ammo_shot_1) * (1 - 0.5*ship2->get_maneuverability()) *
                               0.01f*(rand()%31 + 70.0) * morale_effect_1);
        round_damage_2 = short(3.0 * double(round_ammo_shot_2) * (1 - 0.5*ship1->get_maneuverability()) *
                               0.01f*(rand()%31 + 70.0) * morale_effect_2);

        qDebug() << "";
        qDebug() << "Player damage - " << round_damage_1;
        qDebug() << "NPC damage - " << round_damage_2;
        qDebug() << "";

        // change health
        if (ship1->get_health() > round_damage_2 + 5)
            ship1->set_health(ship1->get_health() - round_damage_2);
        else
        {
            timer1->stop();
            emit update_info();
            loose();
            return;
        }

        ship2->set_health(ship2->get_health() - round_damage_1);



        // change crew
        ship1->set_crew(short(float(ship1->get_crew()) *
                         (1 - 0.3f * float(round_damage_2)/ship1->get_max_health())));
        ship2->set_crew(short(float(ship2->get_crew()) *
                         (1 - 0.3f * float(round_damage_1)/ship2->get_max_health())));

        // change amount of cannons
        if (ship1->get_cannons() >= 10)
            ship1->set_cannons(ship1->get_cannons() - rand() % 3);
        if (ship2->get_cannons() >= 10)
            ship2->set_cannons(ship2->get_cannons() - rand() % 3);

        qDebug() << "";

        qDebug() << "Player health - " << ship1->get_health();
        qDebug() << "Player crew - " << ship1->get_crew();
        qDebug() << "Player cannons - " << ship1->get_cannons();
        qDebug() << "Player ammo - " << ship1->get_ammo();
        qDebug() << "Player maneuverability - " << ship1->get_maneuverability();
        qDebug() << "";

        qDebug() << "NPC health - " << ship2->get_health();
        qDebug() << "NPC crew - " << ship2->get_crew();
        qDebug() << "NPC cannons - " << ship2->get_cannons();
        qDebug() << "NPC ammo - " << ship2->get_ammo();
        qDebug() << "NPC maneuverability - " << ship2->get_maneuverability();
        qDebug() << "";

        if (ship2->get_health() <= 0)
        {
            timer1->stop();
            emit update_info();
            kill();
            return;
        } else
        if (ship2->get_health() < 0.2 * ship2->get_max_health() || !ship2->get_ammo())
        {
            timer1->stop();
            emit update_info();
            emit sink_abordage(3);
            return;
        } else
        if (ship1->get_health() < 0.2 * ship1->get_max_health() || !ship1->get_ammo())
        {
            timer1->stop();
            emit update_info();
            run_away();
            return;
        }
        emit update_info();
    }
}

void Battle::next_move_abordage()
{
    if (timer2->isActive())
    {
        qDebug() << "";
        qDebug() << "New round of abordage.";
        qDebug() << "";

        qDebug() << "Player crew - " << ship1->get_crew();
        qDebug() << "NPC crew - " << ship2->get_crew();

        // count and apply round damage
        round_damage_1 = short(0.2f * morale_effect_1 * float(ship1->get_crew()) *
                               0.01f * (rand()%31 + 70.0));
        round_damage_2 = short(0.2f * morale_effect_2 * float(ship2->get_crew()) *
                               0.01f * (rand()%31 + 70.0));

        qDebug() << "Player damage - " << round_damage_1;
        qDebug() << "NPC damage - " << round_damage_2;

        if (ship1->get_crew() > 10 + round_damage_2)
            ship1->set_crew(ship1->get_crew() - round_damage_2);
        else
        {
            timer2->stop();
            emit update_info();
            loose();
            return;
        }
        if (ship2->get_crew() > round_damage_1)
            ship2->set_crew(ship2->get_crew() - round_damage_1);
        else
        {
            ship2->set_crew(10);
            timer2->stop();
            qDebug() << "Sank npc after abordage";
            change_crew(ship2->get_crew());
            emit update_info();
            win_abordage();
            return;
        }

        if (ship2->get_crew() < 0.2 * ship2->get_max_crew())
        {
            timer2->stop();
            qDebug() << "Let npc away after abordage";
            let_away = true;
            change_crew(ship2->get_crew() / 2);
            emit update_info();
            win_abordage();
            return;
        };
        emit update_info();
    }
}

void Battle::get_goods()
{
    qDebug() << "";
    qDebug() << "Before: ";
    qDebug() << "Player goods: ";
    foreach (Cargo * cargo, ship1->goods)
        qDebug() << cargo->get_name() << " - " << cargo->get_amount();
    qDebug() << "";
    qDebug() << "NPC goods: ";
    foreach (Cargo * cargo, ship2->goods)
        qDebug() << cargo->get_name() << " - " << cargo->get_amount();

    foreach (Cargo * cargo2, ship2->goods)
    {
        foreach (Cargo * cargo1, ship1->goods)
        {
            if (cargo1->get_id() == cargo2->get_id())
            {
                short amount = cargo2->get_amount();
                cargo1->change_amount(amount);
                if (cargo1->get_amount() > 20)
                {
                    amount = cargo1->get_amount() - 20;
                    cargo1->change_amount(-amount);
                }
                else
                    amount = 0;
                cargo2->change_amount(amount - cargo2->get_amount());
            }
        }
    }

    qDebug() << "";
    qDebug() << "After: ";
    qDebug() << "Player goods: ";
    foreach (Cargo * cargo, ship1->goods)
        qDebug() << cargo->get_name() << " - " << cargo->get_amount();
    qDebug() << "";
    qDebug() << "NPC goods: ";
    foreach (Cargo * cargo, ship2->goods)
        qDebug() << cargo->get_name() << " - " << cargo->get_amount();
    emit update_info();
}

void Battle::change_crew(short _amount)
{
    qDebug() << "";
    qDebug() << "Player crew - " << ship1->get_crew();
    qDebug() << "Add " << _amount << " people to crew.";
    qDebug() << "Player morale effect - " << morale_effect_1;
    short new_crew_morale = rand() % 10;
    if (let_away)
        new_crew_morale += 20;
    morale_effect_2 = set_morale_effect(new_crew_morale) * 0.3;
    qDebug() << "New crew morale - " << new_crew_morale;
    qDebug() << "Their morale effect - " << morale_effect_2;
    morale_effect_1 = (morale_effect_1 * ship1->get_crew() + morale_effect_2 * _amount) /
                      ((ship1->get_crew() + _amount) * morale_effect_1);
    emit change_player_morale(morale_effect_1);
    ship1->set_crew(ship1->get_crew() + _amount);
    qDebug() << "Days off harbor morale - " << morale_effect_1;
}

void Battle::after_sea_battle(short _battle_phase)
{
    emit update_info();
    if (_battle_phase == 5)
        kill();
    if (_battle_phase == 4)
    {
        timer2->start(round_time);
        abordage();
    }
}

/*void Battle::change_back_type(Ship *_ship)
{
    if (dynamic_cast<NPC *>(_ship) != 0)
        _ship = dynamic_cast<NPC *>(_ship);
    if (dynamic_cast<Pirate *>(_ship) != 0)
        _ship = dynamic_cast<Pirate *>(_ship);
}*/

void Battle::round_on_sea()
{
    if (player_battle)
        next_move_sea();
}

void Battle::round_of_abordage()
{
    next_move_abordage();
}


