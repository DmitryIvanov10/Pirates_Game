#ifndef GAME_H
#define GAME_H

//biblioteki
#include <QObject> //potrzebne do slotów i sygnałów
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <fstream>
#include <QTimer> //potrzebny do Qtimer'a
#include <vector>
#include <cstdlib>
#include <QList>

//pliki
//#include "ship.h"
#include "player.h"
#include "npc.h"
#include "voronoi_point.h"
#include "wind.h"

class Game : public QObject
{
    Q_OBJECT

    QTimer *timer = new QTimer();
    QGraphicsScene * scene = new QGraphicsScene();
    Player * player = new Player();
    Wind *wind = new Wind();
    QGraphicsView * view = new QGraphicsView(scene);

    int resolution_x = 1366 - 2;
    int resolution_y = 768 - 2;
    int border_x = resolution_x / 5;
    int border_y = resolution_y / 5;

    double scene_x = player->get_x()-resolution_x/2;
    double scene_y = player->get_y()-resolution_y/2;

public:
	static std::vector <Voronoi_point> map;
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

signals:
    //void next_tour();

public slots:
    //void check();
    void center_view();

};

#endif // GAME_H
