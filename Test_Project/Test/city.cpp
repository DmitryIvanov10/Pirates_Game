#include "city.h"

City::City(short _id_voronoi)
{
   id_voronoi = _id_voronoi;
    fraction = 1;
    id = 1;
    active = false;
}

City::City(short _id_voronoi, short _fraction)
{
    id_voronoi = _id_voronoi;
    fraction = _fraction;
    id = 1;
    active = false;
}

City::City(short _id_voronoi, short _fraction, short _id)
{
    id_voronoi = _id_voronoi;
    fraction = _fraction;
    id = _id;
    active = false;
}

short City::show_fraction()
{
    return fraction;
}

float City::show_price(short _good)
{
    return prices[_good];
}

void City::set_state(bool state)
{
    active = state;
}

bool City::in_view()
{
    return active;
}
