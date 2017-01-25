#include "player.h"
#include <QDebug>

Player::Player()
{
    std::srand(time(0));
    in_battle = false;
    in_city = false;
    reset_day();
    model = 3;
    fraction = rand() % 4 + 1;
    set_name();
    set_model_parameters();
    max_food = 60 * ceil(double (max_crew) / 15);
    health = max_health;
    crew = 0.75 * max_crew;
    cannons = initial_cannons;
    ammo = 0.5 * max_ammo;
    maneuverability = max_maneuverability;
    set_angle(225);
    sail_level = 0;
    food = max_food / 2;
    gold = 10000;
    salary = 3;
    set_morale();

    probe->setPixmap(QPixmap(":/img/probe.png"));

    // set cargo
    set_cargo();

    X = 3655;
    Y = 3290;

    //setPixmap(QPixmap(":/Caravel_E_01.png"));
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_A:
        case Qt::Key_Left:
            if (!in_battle && !in_city)
                set_angle(angle+2);
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            if (!in_battle && !in_city)
                set_angle(angle-2);
            break;
        case Qt::Key_W:
        case Qt::Key_Up:
            if (!in_battle && !in_city)
                set_sail_level(1);
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            if (!in_battle && !in_city)
                set_sail_level(0);
            break;
        case Qt::Key_Space:
            colliding_items = collidingItems();
            if (colliding_items.size() != 0)
            {
                foreach (QGraphicsItem * item, colliding_items)
                {
                    if (typeid(* item) == typeid(NPC) ||
                        typeid(* item) == typeid(Pirate))
                    {
                        if (model && health >= max_health / 5 && !in_battle && !in_city)
                            emit start_battle(dynamic_cast<Ship *>(item));
                    }

                    if (typeid(* item) == typeid(City))
                    {
                        if (!in_city && !in_battle)
                            emit start_city(dynamic_cast<City *>(item));
                    }
                }
            }
            break;
        case Qt::Key_Escape:
            emit esc_pressed();
    }

    //qDebug() << angle;
}

void Player::do_tour()
{
    /*if (isUnderMouse())
        qDebug() << "Player is under mouse";*/
    probe->setPos(X + sprite_width/2- 60*sin(angle/180*M_PI),
                  Y + sprite_height/2 - 60*cos(angle/180*M_PI));

    bool go = true;

    if (probe->collidingItems().size() != 0)
    {
        if (typeid(* (probe->collidingItems()[0])) == typeid(Island))
            if (collidingItems().size() != 0)
                go = false;
    } else
        go = true;
    if (go)
    {
        if (!in_battle && !in_city)
            move();
        clamp();
        setPos(X,Y);
    }
}

void Player::clamp()
{
    /*switch(sail_level)
    {
        case 0:
            X -= sin(angle/180*M_PI)*speed*0.3 + shift*sin((float)Wind::angle/180*M_PI)*0.1;
            Y -= cos(angle/180*M_PI)*speed*0.3 + shift*cos((float)Wind::angle/180*M_PI)*0.1;
            break;
        case 1:
            X -= sin(angle/180*M_PI)*speed*0.5 + shift*sin((float)Wind::angle/180*M_PI)*0.5;
            Y -= cos(angle/180*M_PI)*speed*0.5 + shift*cos((float)Wind::angle/180*M_PI)*0.5;
            break;
        case 2:
            X -= sin(angle/180*M_PI)*speed*0.5 + shift*sin((float)Wind::angle/180*M_PI)*1.0;
            Y -= cos(angle/180*M_PI)*speed*0.5 + shift*cos((float)Wind::angle/180*M_PI)*1.0;
            break;
    }*/

    // clamping
    if (X < 0)
    {
        X = 0;
    }
    if (X > 8196)
    {
        X = 8196;
    }
    if (Y < 0)
    {
        Y = 0;
    }
    if (Y > 4608)
    {
        Y = 4608;
    }
}

short Player::get_food()
{
    return food;
}

void Player::set_day_salary()
{
    switch(salary)
    {
        case 1:
            one_day_salary = crew * 0.1;
            salary_morale = 0.2f;
            break;
        case 2:
            one_day_salary = crew * 0.2;
            salary_morale = 0.6f;
            break;
        case 3:
            one_day_salary = crew * 0.5;
            salary_morale = 1.0f;
            break;
        case 4:
            one_day_salary = crew * 1.2;
            salary_morale = 1.6f;
            break;
        case 5:
            one_day_salary = crew * 3;
            salary_morale = 2.0f;
            break;
    }
}

void Player::set_morale()
{
    if (food < max_food/6)
        food_morale = 6 * float(food) / max_food;
    else
        food_morale = 1 + (6 * float(food - max_food/6)) / (5 * max_food);
    if (food_morale < 1)
        food_morale = pow(food_morale, 0.5);
    else
        food_morale = 1 + pow(food_morale - 1, 0.5);
    //qDebug() << "food " << food_morale;
    days_off_harbor_morale *= 0.98f;
    //qDebug() << "days " << days_off_harbor_morale;
    set_day_salary();
    //qDebug() << "Salary " << salary_morale;
    morale = ceil((food_morale*days_off_harbor_morale*salary_morale)*200) - 100;
    //qDebug() << "Morale" << morale;
    if (morale > 100)
        morale = 100;
    if (morale < -100)
        morale = -100;
}

void Player::revolt()
{
    qDebug() << "Revolt";
    emit revolt_signal();
    on_boat(crew / 3);
}

short Player::get_morale()
{
    return morale;
}

int Player::get_gold()
{
    return gold;
}

short Player::get_daily_food()
{
    return one_day_food;
}

short Player::get_max_food()
{
    return max_food;
}

short Player::get_salary()
{
    return salary;
}

void Player::reset_day()
{
    day = 0;
    days_off_harbor_morale = 1.0f / 0.98f;
}

void Player::lower_the_sails()
{
    sail_level = 0;
}

bool Player::change_gold(int _gold)
{
    if (gold + _gold < 0)
        return 1;
    gold += _gold;
    return 0;
}

void Player::set_days_off_harbor_morale(float value)
{
    days_off_harbor_morale = value;
    set_morale();
}

void Player::on_boat(short _crew)
{
    model = 0;
    set_model_parameters();
    set_sprite_angle();
    health = max_health;
    crew = _crew;
    if (crew > max_crew)
        crew = max_crew;
    ammo = 0;
    food = 0;
    morale = 0;
    salary = 1;
    cannons = 0;
}

int Player::get_daily_salary()
{
    return one_day_salary;
}

void Player::next_day()
{
    day++;
    set_day_salary();
    gold -= one_day_salary;
    if (model)
    {
        one_day_food = ceil(double(crew) / 15);
        if (food > one_day_food)
            food -= one_day_food;
        else
            food = 0;

        set_morale();

        if (morale < 0)
        {
            short revolt_probability = rand()%101;
            if (morale >= -50)
            {
                if (revolt_probability <= (rand()%(-morale) + 1))
                {
                    qDebug() << "Day " << day;
                    revolt();
                }
            } else
                if (morale > -100)
                {
                    if (revolt_probability <= (rand()%(-morale - 9) + 20))
                    {
                        qDebug() << "Day " << day;
                        revolt();
                    }
                } else
                {
                    morale = -100;
                    qDebug() << "Day " << day;
                    revolt();
                }
        }
    }
}

void Player::buy_new_ship(short _model)
{
    model = _model;
    set_model_parameters();
    if (cannons > max_cannons)
        cannons = max_cannons;
    if (ammo > max_ammo)
        ammo = max_ammo;
    if (crew > max_crew)
        crew = max_crew;
    max_food = 60 * ceil(double (max_crew) / 15);
    if (food > max_food)
        food = max_food;
    health = max_health;
    maneuverability = max_maneuverability;
}
