#include "player.h"

Player::Player()
{
    model = 1;
    ammo = 50;
    crue = 50;
    health = 100;
    cannons  = 4;
    angle = 90;
    sprite_angle = 2;

    X=0;
    Y=0;

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
            set_angle(angle+5);
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            set_angle(angle-5);
            break;
    }

    qDebug() << angle;
}

void Player::do_tour()
{
    move();
    //setPos(X,Y);
    //qDebug() << "X: " <<  X << ", Y: " << Y;
}
