#include "wind.h"

#include <QDebug>

Wind::Wind()
{
    std::srand(time(0));
    angle = 0;
    strenght = 50;

    setPlainText(QString("Kąt: " + QString::number(angle) + "\nSila: " + QString::number(strenght)));
    setFont(QFont("times", 24));
    setDefaultTextColor(Qt::red);
}

Wind::Wind(double _angle, short _strength)
{
    std::srand(0);
    angle = _angle;
    strenght = _strength;

    setPlainText(QString("Kąt: " + QString::number(angle)));
    setFont(QFont("times", 24));
    setDefaultTextColor(Qt::red);
}

void Wind::norm_all()
{
    if(angle < 0)
        angle += 360;
    else if(angle > 359)
        angle -= 360;
    if(strenght < 0)
        strenght += 101;
    else if(strenght > 100)
        strenght -= 101;
}

void Wind::norm_angle()
{
    if(angle < 0)
        angle += 360;
    else if(angle > 359)
        angle -= 360;
}

void Wind::norm_strength()
{
    if(strenght < 0)
        strenght += 101;
    else if(strenght > 100)
        strenght -= 101;
}

void Wind::change_all()
{

    angle += (rand()%10)-5;
    strenght += (rand()%10)-5;
    norm_all();
}

void Wind::change_all(short angle_delta, short strength_delta)
{
    angle += (rand()%(2*angle_delta+1))-angle_delta;
    strenght += (rand()%(2*strength_delta+1))-strength_delta;
    norm_all();
}

short Wind::get_angle()
{
    return angle;
}

short Wind::get_strength()
{
    return strenght;
}

void Wind::do_tour()
{
    change_frequency ++;
    if(change_frequency >= 1200)
    {
        change_all(200,6);
        setPlainText(QString("Kąt: " + QString::number(angle) + "\nSila: " + QString::number(strenght)));
        change_frequency = 0;
    }
    else if(change_frequency%300 == 0)
    {
        change_all(90,6);
        setPlainText(QString("Kąt: " + QString::number(angle) + "\nSila: " + QString::number(strenght)));
    }
    else if(change_frequency%15 == 0)
    {
        change_all(10,6);
        setPlainText(QString("Kąt: " + QString::number(angle) + "\nSila: " + QString::number(strenght)));
    }
    signal();
}
