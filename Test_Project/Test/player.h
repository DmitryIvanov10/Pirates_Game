#ifndef PLAYER_H
#define PLAYER_H

//pliki
#include "ship.h"
#include "wind.h"
#include "npc.h"
#include "pirate.h"
#include "island.h"
#include "city.h"

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
    int one_day_salary;
    int gold;
    short day;
    float days_off_harbor_morale;
    float food_morale;
    float salary_morale;
    bool collision_with_npc;

    void set_day_salary();
    void set_morale();
    void revolt();

public:
    //konstruktory
    Player();

    //zmienne publiczne
    QGraphicsPixmapItem * probe = new QGraphicsPixmapItem;
    bool in_battle;
    bool in_city;

    //funkcje dostępu
    void keyPressEvent(QKeyEvent * event);
    void clamp();

    short get_morale();
    short get_food();
    int get_gold();
    int get_daily_salary();
    short get_daily_food();
    short get_max_food();
    short get_salary();
    void reset_day();
    void buy_new_ship(short _model);
    void lower_the_sails();
    bool change_gold(int _gold);
    void change_food(int _food);

public slots:
    void do_tour();
    void next_day();
    void set_days_off_harbor_morale(float value);
    void on_boat(short _crew);

signals:
    void revolt_signal();
    void start_battle(Ship * _ship);
    void start_city(City * _city);
    void esc_pressed();
    void click_yes();
    void click_no();
};

#endif // PLAYER_H
