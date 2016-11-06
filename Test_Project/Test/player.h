#ifndef PLAYER_H
#define PLAYER_H

//biblioteki
//#include <QObject>
#include <QGraphicsRectItem> //dziedziczenie itemu z grafik
#include <QKeyEvent> //obługa klawiszy
#include <QDebug> //obsługa konsoli Qt

//pliki
#include "ship.h"

class Player: public QGraphicsRectItem, Ship
{
    Q_OBJECT

public:
    Player();
    void keyPressEvent(QKeyEvent * event);

public slots:
    void move();

signals:


};

#endif // PLAYER_H
