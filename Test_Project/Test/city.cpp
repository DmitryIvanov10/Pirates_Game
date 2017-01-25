#include "city.h"

City::City(short _id_voronoi) : City::City(_id_voronoi, 1, 1) {}

City::City(short _id_voronoi, short _fraction) : City::City(_id_voronoi, _fraction, 1) {}

City::City(short _id_voronoi, short _fraction, short _id)
{
    id_voronoi = _id_voronoi;
    fraction = _fraction;
    id = _id;
    active = false;

    ship_models.push_back(3);
    ship_prices.push_back(6500);
    ship_models.push_back(4);
    ship_prices.push_back(8000);
}

short City::show_fraction()
{
    return fraction;
}

float City::show_price(short _good)
{
    return prices[_good];
}

short City::get_selling_ship_model(int number)
{
    if(number < 0 || number > ship_models.size())
        return -1;
    return ship_models[number];
}

int City::get_selling_ship_price(int number)
{
    if(number < 0 || number > ship_prices.size())
        return -1;
    return ship_prices[number];
}

void City::set_state(bool state)
{
    active = state;
}

bool City::in_view()
{
    return active;
}
