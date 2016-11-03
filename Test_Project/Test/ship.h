#ifndef SHIP_H
#define SHIP_H

//biblioteki
#include <QObject> //potrzebne do slotów i sygnałów
#include <vector> //obsługa wektorów
#include <math.h> //funkcje trygonometryczne

//pliki
#include "wind.h"

class Ship: public QObject
{
    Q_OBJECT

    //lista zmiennych typu short klasy Ship
    //zmienne statku, ważne dla gry w widoku podróży
    short angle; //aktualny kąt o jaki statek jest obrócony
    short ship_model; //model statku
    short ship_angle; //kąt obrotu obrazka ze statkiem, wartość pomiędzy [0,7]
    //zmienne zaopatrzenia, używane przy pojedynkach
    short health; //punkty zdrowia dla statku
    short crue; //ilość ludzi na statku
    short cannons; //ilość armat na statku
    short ammo; //ilość amunicji na statku

    //zmienne typu vector klasy Ship
   std:: vector <short> goods; //ilość przewożonych towarów przez statek, każdy element vector'a to inne dobro (na przykład goods[2] to perły, a goods[5] to sól itd.)

    //lista zimennych typu double klasy Ship
    double X; //aktualna pozycja x
    double Y; //aktualna pozycja y

public:
    //konstruktory
    Ship(); //bezargumentowy, raczej nie będzie używany
    Ship(double x, double y, short ship); //konstruktor tworzący okręt w położeniu x, y o modelu statku ship

    //fukncje dostępu
    double pos (bool i); //funckja zwracająca aktualną pozycję statku dla i=0 x, dla i=1 y
    void move(double x, double y); //prymitywna funkcja ruchu statku, raczej nie będzie używana, ale jest na potrzeby testów
    void move(Wind *a); //pożądna funkcja przemieszczenia uwzględniają nachylenie statku, kąt i siłę wiatru
    short find_angle(); //dobieranie kątu statku za pomocą zmiennej angle


signals:

public slots:
};

#endif // SHIP_H
