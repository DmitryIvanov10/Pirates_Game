#include "player.h"

/*
Player::Player()
{

}
*/

void Player::keyPressEvent(QKeyEvent *event)
{
    //choose the key which has been pressed and react
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
}

void Player::move()
{
    qDebug() << "dziala";
}
