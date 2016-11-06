#include "ship.h"

Ship::Ship()
{
    x=0;
    y=0;
    model=1;
}

Ship::Ship(double _x, double _y, short _model)
{
    x=_x;
    y=_y;
    model=_model;
}

void Ship::move(double _x, double _y)
{
    x=_x;
    y=_y;
}

void Ship::move(Wind *_wind)
{
    double norm = abs((double)abs(_wind->show_angl() - angle) - 180) / 359 + 0.5; //do poprawy! norm powinno  być równe 1 dla angle=a->show_angl() i 0 dla wartości odległych o 180.
    double shift = norm * ((double)_wind->show_str()/100); //to wymaga sprawdzenia, ma zwracać 1 jeśli kąt statku = kąt wiatru, a siła wiatru = 100
    x=shift*sin(angle);
    y=shift*cos(angle);
}

double Ship::pos(bool i)
{
    if(i)
        return y;
    else
        return x;
}

short Ship::find_angle()
{
    for(int i=1; i<9; i++)
    {
        if(angle < i*45)
        {
            sprite_angle = i-1;
            return 0;
        }
    }
    return 1;
}
