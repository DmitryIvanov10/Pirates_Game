#ifndef NPC_H
#define NPC_H

//pliki
#include "ship.h"
#include "voronoi_points.h"

//biblioteki
#include <cstdlib> //liczby losowe
#include <QObject>
#include <time.h>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class NPC: public Ship //, public QGraphicsRectItem
{
    Q_OBJECT

    //zmienne typu short klasy NPC
    short fraction; //frakcja do której okręt należy
    short current_location; //wierzchołek voronoi na którym statek się ostatnio meldował
    short next_location; //wierzchołek voronoi na który statek zmierza
    short previous_location; //wierzchołek voronoi z którego statek zmierza
    short target_location; //cel statku, wierzchołek voronoi
    bool active; //czy jest we view

    //funkcja poszukiwania odległości
    int find_distance(short _id1, short _id2); //zwraca odległość pomiędzy dwoma punktami voronoi
    int find_distance(double _X, double _Y, short _id); //zwraca odległość pomiędzy npc a punktem voronoi

public:
    QGraphicsPixmapItem * flag = new QGraphicsPixmapItem(); //flaga frakcji

    //konstruktory
    NPC();
    NPC(short _start_id, short _finish_id);
    NPC(double _x, double _y, short _model);

    //destructor
    ~NPC();

    //funkcje dostępu
    void find_next (); //funkcja znajdująca kolejny wierzchołek voronoi
    short show_fraction(); //funkcja wyświetlająca frakcję jednostki
    void set_direction(); // funkcja zmienia kąt tak, żeby płynął do next_location
    void set_flag(); //funkcja która wybiera flagę w zależności od frakcji
    void set_state(bool state); //ustawia stan statku (aktywny czy nie)
    void set_cargo(); //ustawia towary statku
    bool in_view();

signals:

public slots:
    void move_to_next_location();
};

#endif // NPC_H
