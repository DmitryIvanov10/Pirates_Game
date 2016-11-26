#ifndef PLAYER_H
#define PLAYER_H

//pliki
#include "ship.h"

//biblioteki
#include <QObject>
#include <QGraphicsRectItem> //dziedziczenie itemu z grafik
#include <QKeyEvent> //obługa klawiszy
#include <QDebug> //obsługa konsoli Qt

class Player: public Ship, public QGraphicsRectItem
{
    Q_OBJECT

public:
    //konstruktory
    Player();

    //funkcje dostępu
    void keyPressEvent(QKeyEvent * event);

public slots:
    void move();

signals:


};

#endif // PLAYER_H
