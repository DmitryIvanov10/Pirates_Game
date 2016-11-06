#include "voronoi_point.h"

Voronoi_point::Voronoi_point(double x, double y)
{
    X=x;
    Y=y;
    id=1;
    harbor=0;
    edge=0;
}

Voronoi_point::Voronoi_point(double x, double y, short _id)
{
    X=x;
    Y=y;
    id=_id;
    harbor=0;
    edge=0;
}

Voronoi_point::Voronoi_point(double x, double y, bool _harbor)
{
    X=x;
    Y=y;
    id=1;
    harbor=_harbor;
    edge=0;
}

Voronoi_point::Voronoi_point(double x, double y, bool _harbor, bool _edge)
{
    X=x;
    Y=y;
    id=1;
    harbor=_harbor;
    edge=_edge;
}

Voronoi_point::Voronoi_point(double x, double y, short _id, bool _harbor, bool _edge)
{
    X=x;
    Y=y;
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
        qDebug() << "Error! To much neighbors for point " << id;
    }
}

double Voronoi_point::pos(bool a)
{
    if(a)
        return Y;
    else
        return X;
}
