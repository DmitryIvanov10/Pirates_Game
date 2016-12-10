#include "player.h"

Player::Player()
{
    model = 1;
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
    double shift = wind_effect * ((double)Wind::strength/100)+0.4;

    /*if(shift * sin(angle / 180 * M_PI) * sail_level > 0 && X - shift * sin(angle / 180 * M_PI) * sail_level > 0)
        X -= shift*sin(angle/180*M_PI)*sail_level;
    else if(shift * sin(angle / 180 * M_PI) * sail_level < 0 && X - shift * sin(angle / 180 * M_PI) * sail_level < 4098)
        X -= shift*sin(angle/180*M_PI)*sail_level;

    if(shift*cos(angle/180*M_PI)*sail_level > 0 && Y - shift*cos(angle/180*M_PI)*sail_level > 0)
        Y -= shift*cos(angle/180*M_PI)*sail_level;
    if(shift*cos(angle/180*M_PI)*sail_level < 0 && Y - shift*cos(angle/180*M_PI)*sail_level < 2304)
        Y -= shift*cos(angle/180*M_PI)*sail_level;*/

    // change of the position on X and Y axis
    X -= shift*sin(angle/180*M_PI)*sail_level;
    Y -= shift*cos(angle/180*M_PI)*sail_level;

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
