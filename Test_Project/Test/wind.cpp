#include "wind.h"

#include <QDebug>

Wind::Wind()
{
    setPlainText(QString("Kąt wiatru: " + QString::number(Wind::angle) + "\nSila wiatru: " + QString::number(Wind::strength)));
    setFont(QFont("times", 24));
    setDefaultTextColor(Qt::red);
}

/*Wind::Wind(double _angle, short _strength)
{
    setPlainText(QString("Kąt: " + QString::number(Wind::angle)));
    setFont(QFont("times", 24));
    setDefaultTextColor(Qt::red);
}*/

/*void Wind::create_wind()
{
    Wind::angle = 0;
    Wind::strength = 50;
}

void Wind::create_wind(double _angle, short _strength)
{
    Wind::angle = _angle;
    Wind::strength = _strength;
}*/

void Wind::norm_all()
{
    norm_angle();
    norm_strength();
}

void Wind::norm_angle()
{
    if(Wind::angle < 0)
        Wind::angle += 360;
    else if(Wind::angle > 359)
        Wind::angle -= 360;
}

void Wind::norm_strength()
{
    if (Wind::strength < 0)
        Wind::strength = 0;
    else if(Wind::strength > 99)
        Wind::strength = 99;
}

void Wind::change_all()
{

    change_all(5, 5);
    norm_all();
}

void Wind::change_all(short angle_delta, short strength_delta)
{
    Wind::angle += (rand()%(2*angle_delta+1))-angle_delta;
    Wind::strength += (rand()%(2*strength_delta+1))-strength_delta;
    norm_all();
}

/*short Wind::get_angle()
{
    return angle;
}

short Wind::get_strength()
{
    return strenght;
}*/

void Wind::do_tour()
{
    change_frequency ++;
    if(change_frequency >= 17*500)
    {
        change_all(180,100);
        setPlainText(QString("Wiatr\nKąt: " + QString::number(angle) + "\nSiła: " + QString::number(strength)));
        change_frequency = 0;
    }
    else if(change_frequency%(17*50) == 0)
    {
        change_all(90,50);
        setPlainText(QString("Wiatr\nKąt: " + QString::number(angle) + "\nSiła: " + QString::number(strength)));
    }
    else if(change_frequency%(17*10) == 0)
    {
        change_all(45,25);
        setPlainText(QString("Wiatr\nKąt: " + QString::number(angle) + "\nSiła: " + QString::number(strength)));
    }
    else if(change_frequency%(17) == 0)
    {
        change_all(5,2);
        setPlainText(QString("Wiatr\nKąt: " + QString::number(angle) + "\nSiła: " + QString::number(strength)));
    }
    //Wind::angle = 0;
    //Wind::strength = 99;

    signal();
}
