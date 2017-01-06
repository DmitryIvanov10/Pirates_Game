#ifndef GAME_H
#define GAME_H

//biblioteki
#include <QObject> //potrzebne do slotów i sygnałów
#include <QGraphicsScene> //scena w której odbywa się gra
#include <QGraphicsItem> //elemrnty wewnątrz sceny
//#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem> //elementy graficzne
//#include <QGraphicsView> //widok wewntrz sceny
#include <fstream> //czytanie plików, aktulanie nie używane
#include <QTimer> //potrzebny do Qtimer'a
#include <vector> //vector
#include <cstdlib>
#include <QList>
#include <QDebug>
#include <QFont> //opcje czcionki
#include <QMouseEvent>
#include <QImage>
#include <QBrush>
#include <QPointF>

//pliki
#include "npc.h"
#include "player.h"
#include "voronoi_point.h"
#include "voronoi_points.h"
#include "wind.h"
#include "island.h"
#include "view.h"
#include "battle.h"

class Game : public QObject
{
    Q_OBJECT

    QTimer *timer = new QTimer(); //zegar odliczający kolejne kroki fizyczne
    QGraphicsScene * scene = new QGraphicsScene(); //scena na której dzieje się gra
    Player * player = new Player(); //statek gracza
    Wind *wind = new Wind(); //wiatr wiejący na mapie
    Voronoi_points * voronoi_points = new Voronoi_points();
    View * view = new View(scene); //widok na scenie

    std::vector <QGraphicsPixmapItem *> sea; //kafelki oceanu
    std::vector <Island *> islands; //wszystkie wyspy na mapie

    std::vector <Battle *> battles; //wszystkie walki

    std::vector <QGraphicsPixmapItem *> hud_img; //graficzna część HUD'u
    std::vector <QGraphicsTextItem *> hud_txt; //tekstowa część HUD'u
    std::vector<QGraphicsPixmapItem *> hud_temp_img; //elementy graficzne pojawiające się na scenie tymczasowo
    std::vector<QGraphicsTextItem *> hud_temp_txt; //elementy tekstowe pojawiające się na scenie tymczasowo
    std::vector<bool> hud_temp_bool; //informacja o użytkowaniu danego elementu tymczasowego
    QGraphicsRectItem * map_rect; //prostokącik na mapie

    QGraphicsPixmapItem * menu_bar = new QGraphicsPixmapItem(); //grafika menu

    std::vector <NPC *> npc_ships; //statki npc na mapie

    int frame_time = 17;
    int game_time = 0;
    int resolution_x = 1366 - 2;
    int resolution_y = 768 - 3;
    int border_x = resolution_x / 4;
    int border_y = resolution_y / 4;

    const int start_npc_amount = 30; //ilość statków NPC
    const int game_day = 200;

    double scene_x = player->get_x()-resolution_x/2; //położenie widoku x
    double scene_y = player->get_y()-resolution_y/2; //położenie widoku y

    bool pause = 0; //if game is paused
    bool menu_bool = 0; //czy menu jest włączone

public:
    //static std::vector <Voronoi_point> map;


    //konstruktory
    Game(QObject *parent = 0); //nowa gra
    Game(std::string a); //wczytanie gry o nazwie a

    void new_game();
    void load_game();

    //funkcje dostępu
    double get_x(short _id);
    double get_y(short _id);
    double get_harbor(short _id);
    double get_edge(short _id);
    short get_neighbour(short _id, short _number);
    void set_hud();
    void set_island(short _x, short _y, QString _pixmap_name);
    void start_stop();
    void show_menu();

signals:
    //void next_tour();
    void new_day();

public slots:
    //void check();
    void count_days();
    void update_states();
    void center_view();
    void start_player_battle(Ship * _ship);
    void end_player_battle();
    //void start_nonplayer_battle(Ship * _ship1, Ship * _ship2);
    void mouse_moved();
    void mose_pressed();
    void reset_timer();
    void esc_pressed();
};

#endif // GAME_H
