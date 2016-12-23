#include "player.h"

Player::Player()
{
    model = 1;
    speed = 1.0;
    ammo = 50;
    crue = 50;
    health = 100;
    cannons  = 4;
    set_angle(90);
    sail_level = 1;
    morale = 100;
    food = 100;

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

void Player::do_tour()
{
    move();
    setPos(X,Y);
}

void Player::move()
{
    double wind_effect = abs(abs(Wind::angle - angle) - 180) / 359 + 0.5; // Liczy effekt wiatru na prędkość statku jako współczynnik - 0.5 przy dokładnie przeciwnym kierunku, 1 - przy tym samym kierunku statku i wiatru
    double shift = wind_effect * ((double)Wind::strength/100) + 0.4;

    switch(sail_level)
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
    }

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
