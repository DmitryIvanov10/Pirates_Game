#ifndef NPC_H
#define NPC_H

//pliki
#include "ship.h"
//biblioteki
#include <cstdlib> //liczby losowe
#include <QObject>

class NPC: public QObject, Ship
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
};

signals:

public slots:


#endif // NPC_H
