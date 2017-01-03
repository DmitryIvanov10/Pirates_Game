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
#include <typeinfo>
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <QPointF>

class Player: public Ship //, public QGraphicsRectItem
{
    Q_OBJECT

    short one_day_food;
    short max_food;
    short food;
    short morale;
    short salary;
    short one_day_salary;
    short gold;
    float days_off_harbor_morale;
    float food_morale;
    float salary_morale;
    short day;

public:
    //konstruktory
    Player();

    //zmienne publiczne
    QGraphicsPixmapItem * probe = new QGraphicsPixmapItem;
    static std::vector<QPointF> island_coordinates;

    //funkcje dostępu
    void keyPressEvent(QKeyEvent * event);
    void clamp();

    short get_morale();
    short get_food();
    void set_day_salary();
    void set_morale();

public slots:
    void do_tour();
    void next_day();

signals:


};

#endif // PLAYER_H
