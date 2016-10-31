#include "voronoi_point.h"

Voronoi_point::Voronoi_point(double x, double y)
{
    X=x;
    Y=y;
    id=1;
    harbor=0;
    edge=0;
}

Voronoi_point::Voronoi_point(double x, double y, short a)
{
    X=x;
    Y=y;
    id=a;
    harbor=0;
    edge=0;
}

Voronoi_point::Voronoi_point(double x, double y, bool a)
{
    X=x;
    Y=y;
    id=1;
    harbor=a;
    edge=0;
}

Voronoi_point::Voronoi_point(double x, double y, bool a, bool b)
{
    X=x;
    Y=y;
    id=1;
    harbor=a;
    edge=b;
}

void Voronoi_point::new_neighbor(short a)
{
    if(neighbors.size() < 3)
    {
        neighbors.push_back(a);
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
