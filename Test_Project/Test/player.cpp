#include "player.h"
#include <QDebug>

Player::Player()
{
    std::srand(time(0));
    model = 3;
    set_model_parameters();
    max_food = 30 * ceil(double (max_crew) / 15);
    health = max_health;
    crew = 0.75 * max_crew;
    cannons = initial_cannons;
    ammo = 0.5 * max_ammo;
    set_angle(90);
    sail_level = 1;
    morale = 100;
    food = max_food / 2;

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
    //choose the key which has been pressed and react

    /*
    switch (event->key())
    {
        case Qt::Key_A:
        case Qt::Key_Left:
            setPos(x()-10,y());
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            setPos(x()+10,y());
            break;
        case Qt::Key_W:
        case Qt::Key_Up:
            setPos(x(),y()-10);
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            setPos(x(),y()+10);
            break;
    }
    */
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

void Player::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Mouse pressed";
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << "Mouse pressed in " << event->pos();
    }

    /*foreach (NPC * ship, npc_ships)
    {
        qDebug() << ship->get_model_name();
        if (ship->get_state())
        {
            qDebug() << ship->get_model_name();
            if (event->x() > ship->get_x() &&
                event->x() < ship->get_x() + ship->get_sprite_width() &&
                event->y() > ship->get_y() &&
                event->y() < ship->get_y() + ship->get_sprite_height())
                qDebug() << "inside NPC ship, which is " << ship->get_model_name();
        }
    }*/
}

void Player::do_tour()
{
    move();
    clamp();
    setPos(X,Y);
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

short Player::get_morale()
{
    return morale;
}

void Player::next_day()
{
    one_day_food = ceil(double(crew) / 15);
    if (food > one_day_food)
        food -= one_day_food;
    else
        food = 0;
    if (morale <= 0)
        morale = 0;
    else
        if (!food)
        {
            morale -= 10;
            crew -= crew / 10;
        }
        else
        if (food <= 5 * one_day_food)
            morale -= 5;
}
