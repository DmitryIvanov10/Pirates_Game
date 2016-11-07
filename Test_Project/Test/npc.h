#ifndef NPC_H
#define NPC_H

//pliki
#include "ship.h"
#include "game.h"

//biblioteki
#include <cstdlib> //liczby losowe
#include <QObject>

class NPC: public Ship
{
    Q_OBJECT

    //zmienne typu short klasy NPC
    short fraction; //frakcja do której okręt należy
    short current_location; //wierzchołek voronoi na którym statek się ostatnio meldował
    short next_location; //wierzchołek voronoi na który statek zmierza
    short target_location; //cel statku, wierzchołek voronoi

public:
    //konstruktory
    NPC();

    //funkcje dostępu
    void find_next (); //funkcja znajdująca kolejny wierzchołek voronoi
    short show_fraction(); //funkcja wyświetlająca frakcję jednostki
    void set_direction(); // funkcja zmienia kąt tak, żeby płynął do next_location

signals:

public slots:
    void move_to_next_location();
};

#endif // NPC_H
