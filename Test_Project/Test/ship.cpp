#include "ship.h"
#include <QDebug>

Ship::Ship()
{
    X=0;
    Y=0;
    model=1;
    set_model_parameters();
}

Ship::Ship(double _x, double _y, short _model)
{
    X=_x;
    Y=_y;
    model=_model;
    set_model_parameters();
}

void Ship::set_model_parameters()
{
    switch(model)
    {
        case 1:
            width = 80;
            height = 80;

            break;
    }
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
    //qDebug() << "kąt statku: " << angle << ", sprite: " << sprite_angle;
}

void Ship::move(double _x, double _y)
{
    X=_x;
    Y=_y;
}

void Ship::move()
{
    //if(! (X < 0 || X > 4098 || Y < 0 || Y > 2304))
    double wind_effect = abs(abs(Wind::angle - angle) - 180) / 359 + 0.5; // Liczy effekt wiatru na prędkość statku jako współczynnik - 0.5 przy dokładnie przeciwnym kierunku, 1 - przy tym samym kierunku statku i wiatru
    double shift = wind_effect * ((double)Wind::strength/100)+0.4;

    X -= shift*sin(angle/180*M_PI)*sail_level*speed;
    Y -= shift*cos(angle/180*M_PI)*sail_level*speed;
}

void Ship::set_sail_level(bool _sign)
{
    if(_sign)
        sail_level++;
    else
        sail_level--;
    if(sail_level<0)
        sail_level=0;
    else if(sail_level > 2)
        sail_level = 2;
}

double Ship::pos(bool i)
{
    if(i)
        return Y + height/2;
    else
        return X + width/2;
}

double Ship::get_x()
{
    return X + width/2;
}

double Ship::get_y()
{
    return Y + height/2;
}

int Ship::get_width()
{
    return width;
}

int Ship::get_height()
{
    return height;
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
            set_sprite_angle();
            return 0;
        }
    }
    if(!temp)
    {
        sprite_angle = 0;
        set_sprite_angle();
        return 0;
    }
    return 1;
}

void Ship::set_sprite_angle()
{
    switch(sprite_angle)
    {
        case 0:
            setPixmap(QPixmap(":/img/Ships/Caravel_01/Caravel_N_01.png"));
            break;
        case 1:
            setPixmap(QPixmap(":/img/Ships/Caravel_01/Caravel_NW_01.png"));
            break;
        case 2:
            setPixmap(QPixmap(":/img/Ships/Caravel_01/Caravel_W_01.png"));
            break;
        case 3:
            setPixmap(QPixmap(":/img/Ships/Caravel_01/Caravel_SW_01.png"));
            break;
        case 4:
            setPixmap(QPixmap(":/img/Ships/Caravel_01/Caravel_S_01.png"));
            break;
        case 5:
            setPixmap(QPixmap(":/img/Ships/Caravel_01/Caravel_SE_01.png"));
            break;
        case 6:
            setPixmap(QPixmap(":/img/Ships/Caravel_01/Caravel_E_01.png"));
            break;
        case 7:
            setPixmap(QPixmap(":/img/Ships/Caravel_01/Caravel_NE_01.png"));
            break;
    }

    setTransformOriginPoint(width/2, height/2);
    setRotation(((-(int)angle-23)%45+23)*0.3);
}

short Ship::get_cannon()
{
    return cannons;
}

short Ship::get_crue()
{
    return crue;
}

short Ship::get_health()
{
    return health;
}

short Ship::get_sail_level()
{
    return sail_level;
}

short Ship::get_ammo()
{
    return ammo;
}
