#include "wind.h"

Wind::Wind(QObject *parent) : QObject(parent)
{
    std::srand(0);
    angle = 0;
    strenght = 50;
}

Wind::Wind(short _angle, short _strength)
{
    std::srand(0);
    angle = _angle;
    strenght = _strength;
}

void Wind::norm_all()
{
    if(angle < 0)
        angle += 360;
    else if(angle > 359)
        angle -= 360;
    if(strenght < 0)
        strenght += 100;
    else if(strenght > 99)
        strenght -= 100;
}

void Wind::norm_angl()
{
    if(angle < 0)
        angle += 360;
    else if(angle > 359)
        angle -= 360;
}

void Wind::norm_str()
{
    if(strenght < 0)
        strenght += 100;
    else if(strenght > 99)
        strenght -= 100;
}

void Wind::change_all()
{

    angle += (rand()%10)-5;
    strenght += (rand()%10)-5;
    norm_all();
}

void Wind::change_all(short angle_delta, short strength_delta)
{
    angle += (rand()%(2*angle_delta))-angle_delta;
    strenght += (rand()%(2*strength_delta))-strength_delta;
    norm_all();
}

short Wind::show_angl()
{
    return angle;
}

short Wind::show_str()
{
    return strenght;
}
