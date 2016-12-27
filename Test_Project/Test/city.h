#ifndef CITY_H
#define CITY_H

//biblioteki
#include <QObject> //potrzebne do slotów i sygnałów
#include <vector> //obsługa wektorów

class City: QObject
{
    Q_OBJECT

    //lista zmiennych klasy City
    short id_voronoi; //najbliższy wierzchołek voronoi
    short fraction; //frakcja do której miasto przynależy
    short id; //niepowtarzalne id portu
    bool active; //czy jest we view

    std::vector <float> prices; //ceny konkretnych dóbr

public:
    //konstrukory
    City(short _id_voronoi); //zmienna voronoi
    City(short _id_voronoi, short _fraction); //zmienne voronoi, fraction
    City(short _id_voronoi, short _fraction, short _id); //zmienne voronoi, fraction, id

    //funkcje dostępu
    void change_fraction(short _fraction); //funkcja zmiany frakcji
    short show_fraction(); //funkcja wyświetlania aktualnej frakcji
    void change_prices(); //funkcja losowej zmiany cen
    void set_state(bool state); // zmienia stan miasta - czy jest aktywny
    bool in_view();
    float show_price(short _good); //funkcja pokazująca cenę obiektu a

signals:

public slots:
};

#endif // CITY_H
