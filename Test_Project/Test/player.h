#ifndef PLAYER_H
#define PLAYER_H

//pliki
#include "ship.h"
#include "wind.h"

//biblioteki
#include <QObject>
#include <QGraphicsRectItem> //dziedziczenie itemu z grafik
#include <QKeyEvent> //obługa klawiszy
#include <QDebug> //obsługa konsoli Qt

class Player: public Ship //, public QGraphicsRectItem
{
    Q_OBJECT

    short food;
    short morale;

public:
    //konstruktory
    Player();

    //funkcje dostępu
    void keyPressEvent(QKeyEvent * event);
    void move();

    short get_morale();
    short get_food();

public slots:
    void do_tour();
    void set_new_day();

signals:


};

#endif // PLAYER_H
