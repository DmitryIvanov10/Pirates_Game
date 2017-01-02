#include "ship.h"
#include <QDebug>

Ship::Ship(double _x, double _y, short _model)
{
    X=_x;
    Y=_y;
    model=_model;
    set_model_parameters();
}

Ship::Ship() : Ship::Ship(0, 0, 1) {}

void Ship::set_model_parameters()
{
    switch(model)
    {
        case 0:
            model_name = "Jolly boat";
            break;
        case 1:
            model_name = "Sloop";
            break;
        case 2:
            model_name = "Cutter";
            break;
        case 3:
            model_name = "Caravel";
            sprite_width = 80;
            sprite_height = 80;
            max_health = 230;
            max_crew = 175;
            initial_cannons = 24;
            max_cannons = 30;
            max_ammo = 150;
            hold_size = 4;
            max_speed = 2.85;
            bladewind_speed = 1.05;
            paddle_speed = 0.3;
            break;
        case 4:
            model_name = "Brig";
            sprite_width = 80;
            sprite_height = 80;
            max_health = 270;
            max_crew = 177;
            initial_cannons = 16;
            max_cannons = 24;
            max_ammo = 120;
            hold_size = 3;
            max_speed = 4.35;
            bladewind_speed = 1.05;
            paddle_speed = 0.4;
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
        /*case 0:
            setPixmap(QPixmap(":/img/Ships/Brig_01/Brig_N_01.png"));
            break;
        case 1:
            setPixmap(QPixmap(":/img/Ships/Brig_01/Brig_NW_01.png"));
            break;
        case 2:
            setPixmap(QPixmap(":/img/Ships/Brig_01/Brig_W_01.png"));
            break;
        case 3:
            setPixmap(QPixmap(":/img/Ships/Brig_01/Brig_SW_01.png"));
            break;
        case 4:
            setPixmap(QPixmap(":/img/Ships/Brig_01/Brig_S_01.png"));
            break;
        case 5:
            setPixmap(QPixmap(":/img/Ships/Brig_01/Brig_SE_01.png"));
            break;
        case 6:
            setPixmap(QPixmap(":/img/Ships/Brig_01/Brig_E_01.png"));
            break;
        case 7:
            setPixmap(QPixmap(":/img/Ships/Brig_01/Brig_NE_01.png"));
            break;*/
    }

    setTransformOriginPoint(sprite_width/2, sprite_height/2);
    setRotation(((-(int)angle-23)%45+23)*0.3);
}

short Ship::get_cannon()
{
    return cannons;
}

short Ship::get_crew()
{
    return crew;
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
