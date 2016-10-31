#include "wind.h"

Wind::Wind(QObject *parent) : QObject(parent)
{
    angle = 0;
    strenght = 50;
}

void Wind::change_all()
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
