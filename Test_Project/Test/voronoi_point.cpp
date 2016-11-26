#include "voronoi_point.h"

Voronoi_point::Voronoi_point(double _x, double _y)
{
    x=_x;
    y=_y;
    id=1;
    harbor=0;
    edge=0;
}

Voronoi_point::Voronoi_point(double _x, double _y, short _id)
{
    x=_x;
    y=_y;
    id=_id;
    harbor=0;
    edge=0;
}

Voronoi_point::Voronoi_point(double _x, double _y, bool _harbor)
{
    x=_x;
    y=_y;
    id=1;
    harbor=_harbor;
    edge=0;
}

Voronoi_point::Voronoi_point(double _x, double _y, bool _harbor, bool _edge)
{
    x=_x;
    y=_y;
    id=1;
    harbor=_harbor;
    edge=_edge;
}

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

short Voronoi_point::get_neighbours(short _number)
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
