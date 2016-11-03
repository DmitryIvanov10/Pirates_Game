#include "ship.h"

Ship::Ship()
{
    X=0;
    Y=0;
    ship_model=1;
}

Ship::Ship(double x, double y, short ship)
{
    X=x;
    Y=y;
    ship_model=ship;
}

void Ship::move(double x, double y)
{
    X=x;
    Y=y;
}

void Ship::move(Wind *a)
{
    double norm = abs((double)abs(a->show_angl() - angle) - 180); //do poprawy! norm powinno  być równe 1 dla angle=a->show_angl() i 0 dla wartości odległych o 180.
    double shift = norm * ((double)a->show_str()/100); //to wymaga sprawdzenia, ma zwracać 1 jeśli kąt statku = kąt wiatru, a siła wiatru = 100
    X=shift*sin(angle);
    Y=shift*cos(angle);
}

double Ship::pos(bool i)
{
    if(i)
        return Y;
    else
        return X;
}

short Ship::find_angle()
{
    for(int i=1; i<9; i++)
    {
        if(angle < i*45)
        {
            ship_angle = i-1;
            return 0;
        }
    }
    return 1;
}
