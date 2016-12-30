#include "voronoi_point.h"

Voronoi_point::Voronoi_point(double _x, double _y) :
    Voronoi_point::Voronoi_point(_x, _y, 1, 0, 0) {}

Voronoi_point::Voronoi_point(double _x, double _y, short _id) :
    Voronoi_point::Voronoi_point(_x, _y, _id, 0, 0) {}

Voronoi_point::Voronoi_point(double _x, double _y, bool _harbor) :
    Voronoi_point::Voronoi_point(_x, _y, 1, _harbor, 0) {}

Voronoi_point::Voronoi_point(double _x, double _y, bool _harbor, bool _edge) :
    Voronoi_point::Voronoi_point(_x, _y, 1, _harbor, _edge) {}

Voronoi_point::Voronoi_point(double _x, double _y, short _id, bool _harbor, bool _edge)
{
    x=_x;
    y=_y;
    id=_id;
    harbor=_harbor;
    edge=_edge;
}

void Voronoi_point::new_neighbor(short _id)
{
    if(neighbors.size() < 3)
    {
        neighbors.push_back(_id);
    }
    else
    {
        qDebug() << "Error! Can't add neighbour " << _id << " to the point " << id;
    }
}

void Voronoi_point::set_neighbours(short _id1)
{
    set_neighbours(_id1, -1, -1);
}

void Voronoi_point::set_neighbours(short _id1, short _id2)
{
    set_neighbours(_id1, _id2, -1);
}

void Voronoi_point::set_neighbours(short _id1, short _id2, short _id3)
{
    new_neighbor(_id1);
    new_neighbor(_id2);
    new_neighbor(_id3);
}

short Voronoi_point::get_neighbour(short _number)
{
    return neighbors[_number % 3]; //dzielone przez 3 ponieważ vector neighbors nie może mieć więcej niż trzech sąsiadów i niechcący uruchomienie tej funkcji dla _number = 3 by mogło uszkodzić program
}

double Voronoi_point::pos(bool a)
{
    if(a)
        return y;
    else
        return x;
}

double Voronoi_point::get_x()
{
    return x;
}

double Voronoi_point::get_y()
{
    return y;
}
