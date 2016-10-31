#ifndef VORONOI_POINT_H
#define VORONOI_POINT_H

#include <vector>
#include <QDebug>

class Voronoi_point
{

    //lista stałych klasy Voronoi_point
    double X; //położenie x punktu
    double Y; //połozenie y punktu
    short id; //niepowtarzalne id punktu
    bool harbor; //informacja o tym czy w punkcie jest port
    bool edge; //informacja o tym czy dany punkt jest na skraju mapy

    std::vector <short> neighbors; //informacja o najbliższych sąsiadach, neighbors.size nie może być większe niż 3

public:
    //konstruktory
    Voronoi_point(double x, double y); //punkt o współżędnych x, y
    Voronoi_point(double x, double y, short a); //punkt o współżędnych x, y, oraz id
    Voronoi_point(double x, double y, bool a); //punkt o współżędnych x, y, oraz harbor
    Voronoi_point(double x, double y, bool a, bool b); //punkt o współżędnych x, y, harbor, oraz edge

    //funkcje dostępu
    void new_neighbor(short a); //funkcja dodawania sąsiadów
    double pos (bool a); //pozycja punktu, dla a=0 x, dla a=1 y
};

#endif // VORONOI_POINT_H
