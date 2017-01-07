#ifndef SHIP_H
#define SHIP_H

#define _USE_MATH_DEFINES

//biblioteki
#include <QObject> //potrzebne do slotów i sygnałów
#include <vector> //obsługa wektorów
#include <math.h> //funkcje trygonometryczne
#include <QString> //dla nazwy statku
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

//pliki
#include "wind.h"
#include "cargo.h"

class Ship: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

protected:
    //lista zmiennych typu short klasy Ship

    //zmienne statku, ważne dla gry w widoku podróży
    double angle; //aktualny kąt o jaki statek jest obrócony
    short model; //id modelu statku
    QString model_name; //nazwa modelu statku
    short sail_level; //poziom rozwinięcia żagli
    float max_speed; //maksymalna prędkość
    float speed; //aktualna prędkość
    float bladewind_speed; //prędkość przeciwko wiatru
    float paddle_speed; //prędkość bez wiatru albo słabym wiatru - na wiosłach
    short sprite_angle; //kąt obrotu obrazka ze statkiem, wartość pomiędzy [0,7]

    //zmienne zaopatrzenia, używane przy pojedynkach
    short max_health; // maksymalne zdrowie dla statku
    short health; //punkty zdrowia dla statku
    short max_crew; // maksymalna ilość ludzi na statku
    short crew; //ilość ludzi na statku
    short initial_cannons; //początkowa iłość armat na danej modeli statku
    short max_cannons; //maksymalna ilość armat na statku
    short cannons; //ilość armat na statku
    float max_maneuverability; // maksymalna zdolność manewrować statku (przydatne w walcę)
    float maneuverability; // zdolność manewrować statku (przydatne w walcę)
    short max_ammo; //maksymalna ilość amunicji na statku
    short ammo; //ilość amunicji na statku
    short hold_size; //rozmiar łądowni

    //zmienne typu vector klasy Ship
    std:: vector <Cargo *> goods; //towary, przewożone przez statek

    //lista zimennych typu double klasy Ship
    double X; //aktualna pozycja x
    double Y; //aktualna pozycja y
    int sprite_width; // width of the sprite
    int sprite_height; // height of the sprite

    QList<QGraphicsItem *> colliding_items;

public:
    //konstruktory
    //Ship(double _x, double _y, short _model); //konstruktor tworzący okręt w położeniu x, y o modelu statku ship
    //Ship(); //bezargumentowy, raczej nie będzie używany

    //destructor
    virtual ~Ship();

    //fukncje dostępu
    double pos (bool i); //funckja zwracająca aktualną pozycję statku dla i=0 x, dla i=1 y
    double get_x(); // get x coordinate of a ship
    double get_y(); // get y coordinate of a ship
    int get_sprite_width(); // get width of the ship pixmap
    int get_sprite_height(); // get height of the ship pixmap
    QString get_model_name(); // get the name of the model
    short get_ammo();
    void set_ammo(short _ammo);
    short get_health();
    short get_max_health();
    void set_health(short _health);
    short get_sail_level();
    short get_crew();
    short get_max_crew();
    void set_crew(short _crew);
    short get_cannons();
    void set_cannons(short _cannons);
    float get_maneuverability();
    void set_maneuverability(short _health);
    short get_hold_size();
    std:: vector <Cargo *> get_goods();
    void set_model_parameters(); // set parameters depending on the model of the ship
    void set_sail_level(bool _sign); //funkcja zmieniająca wartość rozłożenia żagli
    void set_angle(double _angle); // funkcja ustawiająca wartość angle
    void set_sprite_angle();
    void move(double _x, double _y); //prymitywna funkcja ruchu statku, raczej nie będzie używana, ale jest na potrzeby testów
    void move(); //pożądna funkcja przemieszczenia uwzględniają nachylenie statku, kąt i siłę wiatru
    short find_sprite_angle(); //dobieranie kątu statku za pomocą zmiennej angle
    short random_value(short _interval, short _value); //zwraca liczbę losową w okolicach _interval od _value z przeciążeniem do _value
    short random_value(short _interval); //zwraca liczbę losową od 0 do _interval przeciążoną do _interval

signals:

public slots:\
};

#endif // SHIP_H
