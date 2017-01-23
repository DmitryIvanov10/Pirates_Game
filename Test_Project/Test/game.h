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
#include <QApplication> //potrzbne do funkcji zamykającej grę

//pliki
#include "ship.h"
#include "npc.h"
#include "player.h"
#include "voronoi_point.h"
#include "voronoi_points.h"
#include "wind.h"
#include "island.h"
#include "view.h"
#include "battle.h"
#include "city.h"

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
    std::vector <City *> cities; //wszystkie miasta na mapie

    std::vector <Battle *> battles; //wszystkie walki

    std::vector <QGraphicsPixmapItem *> hud_img; //graficzna część HUD'u
    std::vector <QGraphicsTextItem *> hud_txt; //tekstowa część HUD'u
    std::vector <QGraphicsPixmapItem *> hud_temp_img; //elementy graficzne pojawiające się na scenie tymczasowo
    std::vector <QGraphicsTextItem *> hud_temp_txt; //elementy tekstowe pojawiające się na scenie tymczasowo
    std::vector <bool> hud_temp_bool; //informacja o użytkowaniu danego elementu tymczasowego
    QGraphicsRectItem * map_rect; //prostokącik na mapie
    std::vector <QGraphicsPixmapItem *> hud_cargo_img; //obrazki towarów w ładowni
    std::vector <QGraphicsTextItem *> hud_cargo_txt; //tekst odpowiadający towarom

    QGraphicsPixmapItem * menu_bar = new QGraphicsPixmapItem(); //grafika menu
    std::vector <QGraphicsPixmapItem *> menu_buttons; // przyciski dla menu
    std::vector <QGraphicsTextItem *> menu_text; //tekst menu

    QGraphicsPixmapItem * npc_info_bar = new QGraphicsPixmapItem(); //grafika info npc

    std::vector <QGraphicsPixmapItem *> battle_start_menu; // grafika na menu początku walki
    QGraphicsTextItem * battle_start_menu_text = new QGraphicsTextItem(); // tekst menu początku walki
    std::vector <QGraphicsPixmapItem *> battle_screen_img; //obrazki do walki
    std::vector <QGraphicsTextItem *> battle_screen_txt; //tekst do walki
    std::vector<QGraphicsRectItem *> battle_screen_rect; //paski do walki
    QGraphicsTextItem * sink_abordage_menu_text = new QGraphicsTextItem(); // czy grać chcę zacząć abordaż
    QGraphicsTextItem * sink_let_go_menu_text = new QGraphicsTextItem(); // czy grać chcę odpyścić statek
    QGraphicsTextItem * end_battle_menu_text = new QGraphicsTextItem(); // tekst wynika walki
    short end_battle_menu_text_offset; // przemieszczenie tekstu wynika walki

    std::vector <QGraphicsTextItem *> city_menu_text; //tekst menu miasta
    QGraphicsTextItem * city_start_menu_text = new QGraphicsTextItem(); // tekst menu przy przybyciu do miasta

    QGraphicsTextItem * revolt_text = new QGraphicsTextItem();

    QGraphicsTextItem * info_name_text = new QGraphicsTextItem();
    QGraphicsTextItem * info_model_text = new QGraphicsTextItem();
    QGraphicsTextItem * info_health_text = new QGraphicsTextItem();
    QGraphicsTextItem * info_crew_text = new QGraphicsTextItem();
    std::vector <QGraphicsRectItem *> npc_status_bars;

    std::vector <NPC *> npc_ships; //statki npc na mapie

    Ship * battle_ship; // statek z którym walczy player

    City * actual_city; // miasto, do którego dopłynął grać


    bool clicked = false;
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
    bool player_at_battle = 0; //if player is in a battle
    bool player_in_city = 0; //if player in the city
    bool menu_bool = 0; //czy menu jest włączone

    // pomocnicze zmienne dla sprawdzania dodawania i usuwania przycisków lub innych elementów ze sceny
    bool element1_in_scene = false;
    bool element2_in_scene = false;

    bool showing_npc_info = false; // czy pokazuje się info npc w grze
    bool showing_revolt_menu = false; // czy jest otwarte menu buntu
    // position of the npc info bar
    short npc_info_bar_x;
    short npc_info_bar_y;

    void hide_revolt_menu();

public:
    //static std::vector <Voronoi_point> map;
    short battle_phase = 0; //faza walki, 0 - nie ma walki
    short city_phase = 0; //faza miasta, 0 - nie w mieście

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
    void set_city(short _x, short _y, short _voronoi_id, QString _pixmap_name, short _fraction);
    void start_stop();
    void show_menu();
    void battle(short _battle_phase);
    void hide_battle_menu(short _battle_phase);
    void hide_city_menu(short _city_phase);
    void show_first_menu();

signals:
    //void next_tour();
    void new_day();
    void sink_abordage(short _battle_phase);
    void sink_let_go(bool _let_go);
    void run_away();

public slots:
    //void check();
    void show_revolt_menu();
    void show_battle_menu(short _battle_phase);
    void show_city_menu(short _city_phase);
    void show_npc_info(NPC * _ship);
    void hide_npc_info();
    void count_days();
    void update_states();
    void center_view();
    void got_to_city(City * _city);
    void leave_city();
    void start_player_battle(Ship * _ship);
    void end_player_battle(short _status); //0 - don't start battle; 1 - loose, on boat; 2 - loose, ran away; 3 - win, kill; 4 - win, let go
    //void start_nonplayer_battle(Ship * _ship1, Ship * _ship2);
    void mouse_moved();
    void mouse_pressed();
    void mouse_released();
    void reset_timer();
    void delete_npc(NPC * _ship);
    //void delete_pirate(Pirate * _ship);
    void esc_pressed();
    void create_new_npc();
};

#endif // GAME_H
