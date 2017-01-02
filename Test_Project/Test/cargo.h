#ifndef CARGO_H
#define CARGO_H

// biblioteki
#include <QString> //dla nazwy produktu

class Cargo
{
     //lista zmiennych klasy Cargo
    QString name; // nazwa produktu
    short id; //id produktu
    short amount; // ilość

public:
    Cargo();
    Cargo(short _id);
    Cargo(short _id, short _amount);

     //lista funkcji klasy Cargo
    short get_amount();
    QString get_name();
    short get_id();
    void change_amount(short _amount); //zwiększa iłość produktu o zmienną _amount
    void set_name(); // ustawia name dla produktu w zależności od id
};

#endif // CARGO_H
