#ifndef WIND_H
#define WIND_H

//biblioteki
#include <QObject> //potrzebne do slotów i sygnałów
#include <cstdlib> //potrzebne do liczb losowych

class Wind : public QObject
{
    Q_OBJECT

    short angle; //kąt wiatru w stopniach
    short strenght; //siła wiatru, wartości pomiędzy 0 a 99

public:
    //konstruktory
    explicit Wind(QObject *parent = 0); // angle=0, strenght 50
    Wind(short a, short b); //angle=a, strenght=b

    //funkcje normalizacji
    void norm_all(); //normalizacja kątu do zakresów [0 stopni, 360 stopni], oraz siły do wartości [0, 99]
    void norm_angl(); //normalizacja kątu do zakresów [0 stopni, 360 stopni]
    void norm_str(); //normalizacja siły do wartości [0, 99]

    //funkcje dostępu
    void change_all(); //zmiana kątu i siły o losowy czynnik
    void change_all(int a, int b); //zmiana kątu i siły o losowy czynnik w zakresach: kąt o plus/minus a, oraz siła o plus/minus b
    void change_angle(); //zmiana kątu o losowy czynnik
    void change_strenght(); //zmiana siły o losowy czynnik

    short show_angl(); //wyślwietlenie zmiennej angle
    short show_str(); //wyświetlenie zmiennej strenght
signals:

public slots:
};

#endif // WIND_H
