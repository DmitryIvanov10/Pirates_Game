#ifndef CITY_H
#define CITY_H

//biblioteki
#include <QObject> //potrzebne do slotów i sygnałów
#include <QGraphicsPixmapItem>
#include <QString>
#include <vector> //obsługa wektorów

class City: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    //lista zmiennych klasy City
    short id_voronoi; //najbliższy wierzchołek voronoi
    short fraction; //frakcja do której miasto przynależy
    short id; //niepowtarzalne id portu
    QString name; // nazwa miasta
    bool active; //czy jest we view

    std::vector <short> prices; //ceny konkretnych dóbr
    std::vector <short>  stretegic_prices; //ceny surowców strategicznych, kolejno - food, cannons, ammo
    std::vector <short> ship_prices; //ceny statków
    std::vector <short> ship_models; //modele statków do kupienia

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
    short show_price(QString _good); //funkcja pokazująca cenę obiektu _good
    void set_name(QString _name);
    QString get_name();

    short get_selling_ship_model(size_t number);
    int get_selling_ship_price(size_t number);
    QString get_selling_ship_name(size_t number);
    QString get_selling_ship_description(size_t number);
    QString get_selling_ship_img(size_t number);


signals:

public slots:
};

#endif // CITY_H
