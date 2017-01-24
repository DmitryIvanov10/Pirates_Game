#include "cargo.h"

Cargo::Cargo() : Cargo::Cargo(0, 0) {}

Cargo::Cargo(short _id) : Cargo::Cargo(_id, 0) {}

Cargo::Cargo(short _id, short _amount)
{
    if (_amount)
        amount = _amount;
    else
        amount = rand() % 11 + 10;
    if (_id)
        id = _id;
    else
        id = rand() % 12 + 1;
    set_name();
}

short Cargo::get_amount()
{
    return amount;
}

short Cargo::get_id()
{
    return id;
}

QString Cargo::get_name()
{
    return name;
}

void Cargo::change_amount(short _amount)
{
    amount += _amount;
}

void Cargo::set_name()
{
    switch(id)
    {
        case 0:
            name = "empty slot";
            break;
        case 1:
            name = "sugar";
            break;
        case 2:
            name = "coffee";
            break;
        case 3:
            name = "rum";
            break;
        case 4:
            name = "fruits";
            break;
        case 5:
            name = "cotton";
            break;
        case 6:
            name = "spices";
            break;
        case 7:
            name = "tabacco";
            break;
        case 8:
            name = "cocoa";
            break;
        case 9:
            name = "ebony";
            break;
        case 10:
            name = "mahogany";
            break;
        case 11:
            name = "flour";
            break;
        case 12:
            name = "corn";
            break;
    }
}
