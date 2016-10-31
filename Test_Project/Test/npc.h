#ifndef NPC_H
#define NPC_H

#include "ship.h"


class NPC: Ship
{

    //zmienne typu short klasy NPC
    short fraction; //frakcja do której okręt należy
    short current_location; //wierzchołek voronoi na którym statek się ostatnio meldował
    short next_location; //wierzchołek voronoi na który statek zmierza
    short target_location; //cel statku, wierzchołek voronoi

public:
    //konstruktory
    NPC();

    //funkcje dostępu
    void find_angle (); //funkcja znajdująca kąt pod jakim statek powinien się ustawić
    void find_next (); //funkcja znajdująca kolejny wierzchołek voronoi
    short show_fraction(); //funkcja wyświetlająca frakcję jednostki
};

#endif // NPC_H
