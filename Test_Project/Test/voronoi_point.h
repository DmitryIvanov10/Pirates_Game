#ifndef VORONOI_POINT_H
#define VORONOI_POINT_H

//biblioteki
#include <vector> //obsługa wektorów
#include <QDebug> //obsługa konsoli Qt

class Voronoi_point
{

    //lista stałych klasy Voronoi_point
    double x; //położenie x punktu
    double y; //połozenie y punktu
    short id; //niepowtarzalne id punktu
    bool harbor; //informacja o tym czy w punkcie jest port
    bool edge; //informacja o tym czy dany punkt jest na skraju mapy

    std::vector <short> neighbors; //informacja o najbliższych sąsiadach, neighbors.size nie może być większe niż 3

public:
    //konstruktory
    Voronoi_point(double _x, double _y); //punkt o współżędnych x, y
    Voronoi_point(double _x, double _y, short _id); //punkt o współżędnych x, y, oraz id
    Voronoi_point(double _x, double _y, bool _hrabor); //punkt o współżędnych x, y, oraz harbor
    Voronoi_point(double _x, double _y, bool _harbor, bool _edge); //punkt o współżędnych x, y, harbor, oraz edge
    Voronoi_point(double _x, double _y, short _id, bool _harbor, bool _edge);

    //funkcje dostępu
    void new_neighbor(short _id); //funkcja dodawania sąsiadów
    double pos (bool a); //pozycja punktu, dla a=0 x, dla a=1 y
    double get_x(); // get x coordinate of a ship
    double get_y(); // get y coordinate of a ship
};

#endif // VORONOI_POINT_H
