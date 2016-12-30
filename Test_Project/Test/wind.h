#ifndef WIND_H
#define WIND_H

//biblioteki
#include <QObject> //potrzebne do slotów i sygnałów
#include <cstdlib> //potrzebne do liczb losowych
#include <QGraphicsTextItem> //potrzebne do wyświetlania wiatru na ekranie
#include <QFont> //opcje czcionki
#include <time.h>

//pliki
//#include "game.h"

class Wind : public QGraphicsTextItem
{
    Q_OBJECT

    short change_frequency = 0; //częstotliwość zmian wiatru
    //short angle; //kąt wiatru w stopniach
    //short strenght; //siła wiatru, wartości pomiędzy 0 a 99

public:
    static short angle;
    static short strength;

    //konstruktory
    explicit Wind(); // angle=0, strenght 50
    //Wind(double _angle, short _strength); //angle=a, strenght=b
    void create_wind();
    void create_wind(double _angle, short _strength);

    //funkcje normalizacji
    void norm_all(); //normalizacja kątu do zakresów [0 stopni, 360 stopni], oraz siły do wartości [0, 100]
    void norm_angle(); //normalizacja kątu do zakresów [0 stopni, 360 stopni]
    void norm_strength(); //normalizacja siły do wartości [0, 100]

    //funkcje dostępu
    void change_all(); //zmiana kątu i siły o losowy czynnik
    void change_all(short angle_delta, short strenght_delta); //zmiana kątu i siły o losowy czynnik w zakresach: kąt o plus/minus a, oraz siła o plus/minus b
    void change_angle(); //zmiana kątu o losowy czynnik
    void change_strenght(); //zmiana siły o losowy czynnik

    //short get_angle(); //wyślwietlenie zmiennej angle
    //short get_strength(); //wyświetlenie zmiennej strenght
signals:
    void signal();

public slots:
    void do_tour();
};

#endif // WIND_H
