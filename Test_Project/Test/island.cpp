#include "island.h"

Island::Island(QObject *parent) : QObject(parent)
{

}

Island::Island(double _x, double _y, short _texture_number, short _id)
{
    x = _x;
    y = _y;
    texture_number = _texture_number;
    id = _id;
    set_texture();
    active = false;
}

double Island::get_x()
{
    return x;
}

double Island::get_y()
{
    return y;
}

void Island::set_texture()
{
    switch (texture_number)
    {
        case 1:
            setPixmap(QPixmap(""));
            break;
    }

}

void Island::set_state(bool state)
{
    active = state;
}

bool Island::in_view()
{
    return active;
}
