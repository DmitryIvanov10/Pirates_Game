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

void Ship::set_angle(double _angle)
{
    _angle = -(short)floor(_angle) + _angle + (short)floor(_angle) % 360;
    if (_angle < 0)
    {
        _angle += 360;
    }
    angle = _angle;
}

void Ship::move(double _x, double _y)
{
    x=_x;
    y=_y;
}

void Ship::move(Wind *_wind)
{
    double wind_effect = abs(abs(_wind->get_angle() - angle) - 180) / 359 + 0.5; // Liczy effekt wiatru na prędkość statku jako współczynnik - 0.5 przy dokładnie przeciwnym kierunku, 1 - przy tym samym kierunku statku i wiatru
    double shift = wind_effect * ((double)_wind->get_strength()/100);
    y=-shift*cos(angle);
    x=-shift*sin(angle);
}

double Ship::pos(bool i)
{
    if(i)
        return y;
    else
        return x;
}

double Ship::get_x()
{
    return x;
}

double Ship::get_y()
{
    return y;
}

short Ship::find_sprite_angle()
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
