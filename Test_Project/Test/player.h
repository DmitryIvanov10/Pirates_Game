#ifndef PLAYER_H
#define PLAYER_H

//pliki
#include "ship.h"
#include "wind.h"

//biblioteki
#include <QObject>
#include <QGraphicsRectItem> //dziedziczenie itemu z grafik
#include <QKeyEvent> //obługa klawiszy
#include <QMouseEvent>
#include <QDebug> //obsługa konsoli Qt
#include <time.h>
#include <math.h>
#include <cstdlib>

class Player: public Ship //, public QGraphicsRectItem
{
    Q_OBJECT

    short one_day_food;
    short max_food;
    short food;
    short morale;

public:
    //konstruktory
    Player();

    //funkcje dostępu
    void keyPressEvent(QKeyEvent * event);
    void mousePressEvent(QMouseEvent *event);
    void clamp();

    short get_morale();
    short get_food();

public slots:
    void do_tour();
    void next_day();

signals:


};

#endif // PLAYER_H
