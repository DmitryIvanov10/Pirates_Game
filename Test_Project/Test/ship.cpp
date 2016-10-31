#include "ship.h"

Ship::Ship()
{
    X=0;
    Y=0;
    ship_model=1;
}

Ship::Ship(double x, double y, short ship)
{
    X=x;
    Y=y;
    ship_model=ship;
}

void Ship::move(double x, double y)
{
    X=x;
    Y=y;
}

double Ship::pos(bool i)
{
    if(i)
        return Y;
    else
        return X;
}
