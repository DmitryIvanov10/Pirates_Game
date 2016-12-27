#ifndef GAME_H
#define GAME_H

//biblioteki
#include <QObject> //potrzebne do slotów i sygnałów
#include <QGraphicsScene>
#include <QGraphicsItem>
//#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <fstream>
#include <QTimer> //potrzebny do Qtimer'a
#include <vector>
#include <cstdlib>
#include <QList>
#include <QDebug>
#include <QFont> //opcje czcionki

//pliki
#include "npc.h"
#include "player.h"
#include "voronoi_point.h"
#include "voronoi_points.h"
#include "wind.h"
#include "island.h"

class Game : public QObject
{
    Q_OBJECT

    QTimer *timer = new QTimer(); //zegar odliczający kolejne kroki fizyczne
    QGraphicsScene * scene = new QGraphicsScene(); //scena na której dzieje się gra
    Player * player = new Player(); //statek gracza
    Wind *wind = new Wind(); //wiatr wiejący na mapie
    Voronoi_points * voronoi_points = new Voronoi_points();
    QGraphicsView * view = new QGraphicsView(scene); //widok na scenie

    std::vector <QGraphicsPixmapItem *> sea; //kafelki oceanu
    std::vector <Island *> islands; //wszystkie wyspy na mapie

    std::vector <QGraphicsPixmapItem *> hud_img; //graficzna część HUD'u
    std::vector <QGraphicsTextItem *> hud_txt; //tekstowa część HUD'u
    QGraphicsRectItem * map_rect;

    std::vector <NPC *> npc_ships; //statki npc na mapie

    int frame_time = 17;
    int game_time = 0;
    int resolution_x = 1366 - 2;
    int resolution_y = 768 - 3;
    int border_x = resolution_x / 4;
    int border_y = resolution_y / 4;

    const int start_npc_amount = 30; //ilość statków NPC
    const int game_day = 600;

    double scene_x = player->get_x()-resolution_x/2; //położenie widoku x
    double scene_y = player->get_y()-resolution_y/2; //położenie widoku y

public:
    //static std::vector <Voronoi_point> map;


    //konstruktory
    explicit Game(QObject *parent = 0); //nowa gra


    Game(std::string a); //wczytanie gry o nazwie a

    void new_game();
    void load_game();

    //metody konstruktora


    //funkcje dostępu
    double get_x(short _id);
    double get_y(short _id);
    double get_harbor(short _id);
    double get_edge(short _id);
    short get_neighbour(short _id, short _number);
    void set_hud();

signals:
    //void next_tour();
    void new_day();

public slots:
    //void check();
    void count_days();
    void update_states();
    void center_view();
};

#endif // GAME_H
