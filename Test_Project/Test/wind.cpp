#include "wind.h"

Wind::Wind(QObject *parent) : QObject(parent)
{
    std::srand(0);
    angle = 0;
    strenght = 50;
}

Wind::Wind(short a, short b)
{
    std::srand(0);
    angle = a;
    strenght = b;
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

    angle += (rand()%100)-50;
    strenght += (rand()%40)-20;
    norm_all();
}

void Wind::change_all(int a, int b)
{
    angle += (rand()%(2*a))-a;
    strenght += (rand()%(2*b))-b;
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
