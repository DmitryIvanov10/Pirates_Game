#include "city.h"

City::City(short _id_voronoi)
{
   id_voronoi = _id_voronoi;
    fraction = 1;
    id = 1;
}

City::City(short a, short b)
{
    id_voronoi = a;
    fraction = b;
    id = 1;
}

City::City(short a, short b, short c)
{
    id_voronoi = a;
    fraction = b;
    id = c;
}

short City::show_fraction()
{
    return fraction;
}

float City::show_price(short a)
{
    return prices[a];
}
