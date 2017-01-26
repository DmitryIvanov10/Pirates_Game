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

    // health [0]
    prices.push_back(100);
    // cannons [1]
    prices.push_back(35);
    // ammunition [2]
    prices.push_back(10);
}

short City::show_fraction()
{
    return fraction;
}

short City::show_price(QString _good)
{
    if (_good ==  "health")
        return prices[0];

    if (_good ==  "cannons")
        return prices[1];

    if (_good ==  "ammo")
        return prices[2];
}

void City::set_name(QString _name)
{
    name = _name;
}

QString City::get_name()
{
    return name;
}

short City::get_selling_ship_model(size_t number)
{
    if(number < 0 || number > ship_models.size())
        return -1;
    return ship_models[number];
}

int City::get_selling_ship_price(size_t number)
{
    if(number < 0 || number > ship_prices.size())
        return -1;
    return ship_prices[number];
}

QString City::get_selling_ship_name(size_t number)
{
    if(number < 0 || number > ship_models.size())
        return "Wrong number";
    switch (ship_models[number])
    {
    case 1:
        return QString("Sloop");
        break;
    case 2:
        return QString("Cutter");
        break;
    case 3:
        return QString("Caravel");
        break;
    case 4:
        return QString("Brig");
        break;
    case 5:
        return QString("Galeon");
        break;
    case 6:
        return QString("Fregat");
        break;
    case 7:
        return QString("Battleship");
        break;
    default:
        return QString("Wrong model");
    }
}

QString City::get_selling_ship_description(size_t number)
{
    if(number < 0 || number > ship_models.size())
        return "Wrong number";
    switch (ship_models[number])
    {
    case 1:
        return QString("Sloop descripion");
        break;
    case 2:
        return QString("Cutter descripion");
        break;
    case 3:
        return QString("Caravel descripion");
        break;
    case 4:
        return QString("Brig descripion");
        break;
    case 5:
        return QString("Galeon descripion");
        break;
    case 6:
        return QString("Fregat descripion");
        break;
    case 7:
        return QString("Battleship descripion");
        break;
    default:
        return QString("Wrong model descripion");

    }
}

QString City::get_selling_ship_img(size_t number)
{
    if(number < 0 || number > ship_models.size())
        return "Wrong number";
    switch (ship_models[number])
    {
    case 1:
        return QString("");
        break;
    case 2:
        return QString("");
        break;
    case 3:
        return QString(":/Caravel_SE_01.png");
        break;
    case 4:
        return QString(":/Brig_SE_01.png");
        break;
    case 5:
        return QString("Galeon");
        break;
    case 6:
        return QString("Fregat");
        break;
    case 7:
        return QString("Battleship");
        break;
    default:
        return QString("Wrong model img");
    }
}

void City::set_state(bool state)
{
    active = state;
}

bool City::in_view()
{
    return active;
}
