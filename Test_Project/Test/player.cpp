#include "player.h"
#include <QDebug>

Player::Player()
{
    std::srand(time(0));
    day = 0;
    model = 3;
    days_off_harbor_morale = 1.0f / 0.98;
    set_model_parameters();
    max_food = 60 * ceil(double (max_crew) / 15);
    health = max_health;
    crew = 0.75 * max_crew;
    cannons = initial_cannons;
    ammo = 0.5 * max_ammo;
    set_angle(90);
    sail_level = 1;
    //morale = 100;
    food = max_food / 2;
    gold = 10000;
    salary = 3;
    set_morale();

    probe->setPixmap(QPixmap(":/img/probe.png"));

    // set cargo
    for (int i=0; i<hold_size; i++)
    {
        goods.push_back(new Cargo());
        qDebug() << goods[i]->get_name() << ": " << goods[i]->get_amount();
    }

    X = 4000;
    Y = 2000;

    //setPixmap(QPixmap(":/Caravel_E_01.png"));
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_A:
        case Qt::Key_Left:
            set_angle(angle+2);
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            set_angle(angle-2);
            break;
        case Qt::Key_W:
        case Qt::Key_Up:
            set_sail_level(1);
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            set_sail_level(0);
            break;
    }

    //qDebug() << angle;
}

void Player::do_tour()
{
    probe->setPos(X + sprite_width/2- 60*sin(angle/180*M_PI),
                  Y + sprite_height/2 - 60*cos(angle/180*M_PI));

    bool go = true;

    if (probe->collidingItems().size() != 0)
    {

        short i = 0;
        while (i<Player::island_coordinates.size() && go)
        {
            if (probe->collidingItems()[0]->pos() == Player::island_coordinates[i])
                if (collidingItems().size() != 0)
                    go = false;
            i++;
        }
    } else
        go = true;
    if (go)
    {
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
            one_day_salary = crew * 1;
            salary_morale = 0.2f;
            break;
        case 2:
            one_day_salary = crew * 3;
            salary_morale = 0.6f;
            break;
        case 3:
            one_day_salary = crew * 5;
            salary_morale = 1.0f;
            break;
        case 4:
            one_day_salary = crew * 8;
            salary_morale = 1.6f;
            break;
        case 5:
            one_day_salary = crew * 10;
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
    qDebug() << "food " << food_morale;
    days_off_harbor_morale *= 0.98;
    qDebug() << "days " << days_off_harbor_morale;
    set_day_salary();
    qDebug() << "Salary " << salary_morale;
    morale = ceil((food_morale*days_off_harbor_morale*salary_morale)*200) - 100;
    qDebug() << "Morale" << morale;
    if (morale > 100)
        morale = 100;
    if (morale < -100)
        morale = -100;
}

short Player::get_morale()
{
    return morale;
}

void Player::next_day()
{
    day++;
    if (model)
    {
        one_day_food = ceil(double(crew) / 15);
        if (food > one_day_food)
            food -= one_day_food;
        else
            food = 0;

        set_morale();

        if (morale < 0)
            if (morale >= -50)
            {
                if (rand()%101 <= (rand()%(-morale) + 1))
                {
                    qDebug() << "Day " << day;
                    qDebug() << "Revolt";
                    model = 0;
                }
            } else
                if (morale >= -100)
                {
                    if (rand()%101 <= (rand()%(-morale - 9) + 20))
                    {
                        qDebug() << "Day " << day;
                        qDebug() << "Revolt";
                        model = 0;
                    }
                } else
                {
                    morale = -100;
                    qDebug() << "Day " << day;
                    qDebug() << "Revolt";
                    model = 0;
                }
    }
}
