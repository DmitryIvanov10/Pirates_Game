#ifndef PIRATE_H
#define PIRATE_H

//pliki
#include "ship.h"
#include "game.h"

//biblioteki
#include <cstdlib> //liczby losowe
#include <QObject>
#include <time.h>

class Pirate: public Ship
{
    Q_OBJECT

    //zmienne typu short klasy NPC
    bool active; // czy jest gotowy do walki
    short current_location; //wierzchołek voronoi na którym statek się ostatnio meldował
    short next_location; //wierzchołek voronoi na który statek zmierza
    short previous_location; //wierzchołek voronoi z którego statek zmierza
    short target_location; //cel statku, wierzchołek voronoi

    //funkcje zarządzania pływaniem
    int find_distance(short _id1, short _id2); //zwraca odległość pomiędzy dwoma punktami voronoi
    int find_distance(double _X, double _Y, short _id); //zwraca odległość pomiędzy npc a punktem voronoi
    void set_direction(); // funkcja zmienia kąt tak, żeby płynął do next_location
    void find_next (); //funkcja znajdująca kolejny wierzchołek voronoi

public:
    Pirate();
    Pirate(short _start_id);

    //destructor
    ~Pirate();

    //funkcje dostępu
    short show_fraction(); //funkcja wyświetlająca frakcję jednostki

signals:

public slots:
    //void move_to_next_location();
};

#endif // PIRATE_H
