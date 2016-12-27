#ifndef SHIP_H
#define SHIP_H

//biblioteki
#include <QObject> //potrzebne do slotów i sygnałów
#include <vector> //obsługa wektorów
#include <math.h> //funkcje trygonometryczne
#include <QGraphicsPixmapItem>

//pliki
#include "wind.h"

class Ship: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

protected:
    //lista zmiennych typu short klasy Ship

    //zmienne statku, ważne dla gry w widoku podróży
    double angle; //aktualny kąt o jaki statek jest obrócony
    short model; //model statku
    short sail_level; //poziom rozwinięcia żagli
    double speed;
    short sprite_angle; //kąt obrotu obrazka ze statkiem, wartość pomiędzy [0,7]

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
    int width; // width of the sprite
    int height; // height of the sprite

public:
    //konstruktory
    Ship(); //bezargumentowy, raczej nie będzie używany
    Ship(double _x, double _y, short _model); //konstruktor tworzący okręt w położeniu x, y o modelu statku ship

    //fukncje dostępu
    double pos (bool i); //funckja zwracająca aktualną pozycję statku dla i=0 x, dla i=1 y
    double get_x(); // get x coordinate of a ship
    double get_y(); // get y coordinate of a ship
    int get_width(); // get width of the ship pixmap
    int get_height(); // et height of the ship pixmap
    short get_ammo();
    short get_health();
    short get_sail_level();
    short get_crue();
    short get_cannon();
    void set_model_parameters(); // set parameters depending on the model of the ship
    void set_sail_level(bool _sign); //funkcja zmieniająca wartość rozłożenia żagli
    void set_angle(double _angle); // funkcja ustawiająca wartość angle
    void set_sprite_angle();
    void move(double _x, double _y); //prymitywna funkcja ruchu statku, raczej nie będzie używana, ale jest na potrzeby testów
    void move(); //pożądna funkcja przemieszczenia uwzględniają nachylenie statku, kąt i siłę wiatru
    short find_sprite_angle(); //dobieranie kątu statku za pomocą zmiennej angle


signals:

public slots:\
};

#endif // SHIP_H
