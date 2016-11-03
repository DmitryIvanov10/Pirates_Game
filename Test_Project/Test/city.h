#ifndef CITY_H
#define CITY_H

//biblioteki
#include <QObject> //potrzebne do slotów i sygnałów
#include <vector> //obsługa wektorów

class City: QObject
{
    Q_OBJECT

    //lista zmiennych klasy City
    short voronoi; //najbliższy wierzchołek voronoi
    short fraction; //frakcja do której miasto przynależy
    short id; //niepowtarzalne id portu

    std::vector <float> prices; //ceny konkretnych dóbr

public:
    //konstrukory
    City(short a); //zmienna voronoi
    City(short a, short b); //zmienne voronoi, fraction
    City(short a, short b, short c); //zmienne voronoi, fraction, id

    //funkcje dostępu
    void change_fraction(short a); //funkcja zmiany frakcji
    short show_fraction(); //funkcja wyświetlania aktualnej frakcji
    void change_prices(); //funkcja losowej zmiany cen
    float show_price(short a); //funkcja pokazująca cenę obiektu a

signals:

public slots:
};

#endif // CITY_H
