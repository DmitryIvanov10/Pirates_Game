#include "ship.h"
#include <QDebug>

Ship::Ship()
{
    X=0;
    Y=0;
    model=1;
}

Ship::Ship(double _x, double _y, short _model)
{
    X=_x;
    Y=_y;
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
    find_sprite_angle();
    qDebug() << "kąt statku: " << angle << ", sprite: " << sprite_angle;
}

void Ship::move(double _x, double _y)
{
    X=_x;
    Y=_y;
}

void Ship::move()
{
    double wind_effect = abs(abs(Wind::angle - angle) - 180) / 359 + 0.5; // Liczy effekt wiatru na prędkość statku jako współczynnik - 0.5 przy dokładnie przeciwnym kierunku, 1 - przy tym samym kierunku statku i wiatru
    double shift = wind_effect * ((double)Wind::strength/100);
    X -= shift*sin(angle/180*M_PI);
    Y -= shift*cos(angle/180*M_PI);
}

double Ship::pos(bool i)
{
    if(i)
        return Y;
    else
        return X;
}

double Ship::get_x()
{
    return X;
}

double Ship::get_y()
{
    return Y;
}

short Ship::find_sprite_angle()
{
    bool temp = 0;
    for(int i=1; i<9; i++)
    {
        if(angle < i*45 - 23)
        {
            sprite_angle = i-1;
            temp = 1;
            return 0;
        }
    }
    if(!temp)
    {
        sprite_angle = 0;
        return 0;
    }
    return 1;
}
