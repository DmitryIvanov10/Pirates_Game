#include "ship.h"
#include <QDebug>

/*Ship::Ship(double _x, double _y, short _model)
{
    X=_x;
    Y=_y;
    model=_model;
    set_model_parameters();
}

Ship::Ship() : Ship::Ship(0, 0, 1) {}*/

void Ship::set_cargo()
{
    while (goods.size() > 0)
        goods.pop_back();

    for (size_t i=0; i<hold_size; i++)
    {
        bool not_ok = true;
        while (not_ok)
        {
            goods.push_back(new Cargo());
            for (size_t j=0; j<i; j++)
            {
                if (goods[i]->get_id() == goods[j]->get_id())
                {
                    goods.pop_back();
                    break;
                }
            }
            if (goods.size() == i+1)
                not_ok = false;
        }
    }
}

Ship::~Ship()
{
    //qDebug() << "Ship deleted.";
}

void Ship::set_model_parameters()
{
    switch(model)
    {
        case 0:
            model_name = "Boat";
            sprite_width = 40;
            sprite_height = 40;
            max_health = 5;
            max_crew = 15;
            initial_cannons = 0;
            max_cannons = 0;
            max_ammo = 0;
            hold_size = 0;
            max_speed = 0.4f;
            bladewind_speed = 0.4f;
            paddle_speed = 0.4f;
            max_maneuverability = 2.0f;
            break;
        case 1:
            model_name = "Sloop";
            sprite_width = 60;
            sprite_height = 60;
            max_health = 50;
            max_crew = 66;
            initial_cannons = 12;
            max_cannons = 16;
            max_ammo = 80;
            hold_size = 2;
            max_speed = 4.05f;
            bladewind_speed = 2.355f;
            paddle_speed = 0.9f;
            max_maneuverability = 1.0f;
            break;
        case 2:
            model_name = "Cutter";
            sprite_width = 60;
            sprite_height = 60;
            max_health = 80;
            max_crew = 100;
            initial_cannons = 16;
            max_cannons = 20;
            max_ammo = 100;
            hold_size = 2;
            max_speed = 3.7f;
            bladewind_speed = 2.0f;
            paddle_speed = 1.0f;
            max_maneuverability = 0.9f;
            break;
        case 3:
            model_name = "Caravel";
            sprite_width = 80;
            sprite_height = 80;
            max_health = 115;
            max_crew = 175;
            initial_cannons = 24;
            max_cannons = 30;
            max_ammo = 300;
            hold_size = 4;
            max_speed = 2.85f;
            bladewind_speed = 1.05f;
            paddle_speed = 0.3f;
            max_maneuverability = 0.45f;
            break;
        case 4:
            model_name = "Brig";
            sprite_width = 80;
            sprite_height = 80;
            max_health = 135;
            max_crew = 177;
            initial_cannons = 16;
            max_cannons = 24;
            max_ammo = 240;
            hold_size = 3;
            max_speed = 4.35f;
            bladewind_speed = 1.05f;
            paddle_speed = 0.4f;
            max_maneuverability = 0.65f;
            break;
        case 5:
            model_name = "Galeon";
            break;
        case 6:
            model_name = "Fregat";
            break;
        case 7:
            model_name = "Battleship";
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
    /*double wind_effect = ((double)(abs(abs(Wind::angle - angle) - 180)) / 180)
            * (max_speed - bladewind_speed) + bladewind_speed; // Liczy effekt wiatru na prędkość statku, gdy wynik - bladewind_speed przy dokładnie przeciwnym kierunku, speed - przy tym samym kierunku statku i wiatru
    double actual_speed = wind_effect * ((double)Wind::strength/100) * 0.5 * double(sail_level);
    if (actual_speed < paddle_speed && sail_level)
        actual_speed = paddle_speed;

    X -= actual_speed*sin(angle/180*M_PI);
    Y -= actual_speed*cos(angle/180*M_PI);*/
    speed = (((double)(abs(abs(Wind::angle - angle) - 180)) / 180)
            * (max_speed - bladewind_speed) + bladewind_speed) *
            ((double)Wind::strength/100) * 0.5 * double(sail_level);
    if (speed < paddle_speed && sail_level)
        speed = paddle_speed;

    X -= speed*sin(angle/180*M_PI);
    Y -= speed*cos(angle/180*M_PI);

    /*if (speed < (max_speed * 0.1 * double(sail_level)))
        qDebug() << speed << " " << sail_level;*/
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
        return Y + sprite_height/2;
    else
        return X + sprite_width/2;
}

double Ship::get_x()
{
    return X + sprite_width/2;
}

double Ship::get_y()
{
    return Y + sprite_height/2;
}

int Ship::get_sprite_width()
{
    return sprite_width;
}

int Ship::get_sprite_height()
{
    return sprite_height;
}

QString Ship::get_model_name()
{
    return model_name;
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
            setPixmap(QPixmap(":/" + model_name + "_N_01.png"));
            break;
        case 1:
            setPixmap(QPixmap(":/" + model_name + "_NW_01.png"));
            break;
        case 2:
            setPixmap(QPixmap(":/" + model_name + "_W_01.png"));
            break;
        case 3:
            setPixmap(QPixmap(":/" + model_name + "_SW_01.png"));
            break;
        case 4:
            setPixmap(QPixmap(":/" + model_name + "_S_01.png"));
            break;
        case 5:
            setPixmap(QPixmap(":/" + model_name + "_SE_01.png"));
            break;
        case 6:
            setPixmap(QPixmap(":/" + model_name + "_E_01.png"));
            break;
        case 7:
            setPixmap(QPixmap(":/" + model_name + "_NE_01.png"));
            break;
    }

    setTransformOriginPoint(50, 50);
    setRotation(((-(int)angle-23)%45+23)*0.3);
}

short Ship::get_cannons()
{
    return cannons;
}

void Ship::set_cannons(short _cannons)
{
    cannons = _cannons;
}

float Ship::get_maneuverability()
{
    return maneuverability;
}

void Ship::set_maneuverability(short _health)
{
    maneuverability = 0.2f * max_maneuverability * ceil(5 * (double(_health) / double(max_health)));
}

short Ship::get_hold_size()
{
    return hold_size;
}

std::vector<Cargo *> Ship::get_goods()
{
    return goods;
}

short Ship::get_crew()
{
    return crew;
}

short Ship::get_max_crew()
{
    return max_crew;
}

void Ship::set_crew(short _crew)
{
    crew = _crew;
}

short Ship::get_health()
{
    return health;
}

short Ship::get_max_health()
{
    return max_health;
}

void Ship::set_health(short _health)
{
    health = _health;
}

short Ship::get_sail_level()
{
    return sail_level;
}

short Ship::get_ammo()
{
    return ammo;
}

void Ship::set_ammo(short _ammo)
{
    ammo = _ammo;
}

short Ship::random_value(short _interval, short _value)
{
    double a = 1;
    for (int i=0; i<2; i++)
    {
        a *= ((double) rand() / (RAND_MAX));
    }

    if (_value)
    {
        return _value + short(double(_interval)*a)*((rand() % 2) * 2 - 1);
    } else
    {
        return _interval - short(double(_interval)*a*0.25);
    }
}

short Ship::random_value(short _interval)
{
    return random_value(_interval, 0);
}
