#include "game.h"
#include "wind.h"
#include <QDebug>

Game::Game(QObject *parent) : QObject(parent)
{  
    // create map
    new_game();

    // create a scene
    QGraphicsScene * scene = new QGraphicsScene();

    // create an item to put into the scene
    Player * rect = new Player();
    rect->setRect(0,0,100,100);
    scene->addItem(rect);

    // create an npc to put into the scene
    NPC * npc_ship = new NPC();

    // create wind and put into the scene
    Wind *wind = new Wind();
    scene->addItem(wind);


    // add a view
    QGraphicsView * view = new QGraphicsView(scene);

    //make item focus
    rect->setFlag(QGraphicsItem::ItemIsFocusable);
    rect->setFocus();

    connect (timer, SIGNAL(timeout()), rect, SLOT(move()));
    connect (timer, SIGNAL(timeout()), wind, SLOT(do_tour()));
    timer->start(17);

    view->show();
}

Game::Game(std::string a)
{
    std::ifstream load(a.c_str());
    if(load)
    {
        //to do
    }
}

void Game::new_game()
{
    qDebug() << "Create map.";
    short iterate = 1;
    Game::map.push_back(Voronoi_point(0.0, 0.0, (short)0));
    Game::map[iterate-1].new_neighbor(-1);
    Game::map[iterate-1].new_neighbor(-1);
    Game::map[iterate-1].new_neighbor(-1);
    Game::map.push_back(Voronoi_point( 123.0, 463.0, iterate++));
    Game::map[iterate-1].new_neighbor(2);
    Game::map[iterate-1].new_neighbor(-1);
    Game::map[iterate-1].new_neighbor(-1);
    Game::map.push_back(Voronoi_point( 149, 440, iterate++));
    Game::map[iterate-1].new_neighbor(1);
    Game::map[iterate-1].new_neighbor(3);
    Game::map[iterate-1].new_neighbor(7);
    Game::map.push_back(Voronoi_point( 157,305 , iterate++));
    Game::map[iterate-1].new_neighbor(2);
    Game::map[iterate-1].new_neighbor(4);
    Game::map[iterate-1].new_neighbor(-1);
    Game::map.push_back(Voronoi_point(259, 107, iterate++));
    Game::map[iterate-1].new_neighbor(3);
    Game::map[iterate-1].new_neighbor(5);
    Game::map[iterate-1].new_neighbor(-1);
    Game::map.push_back(Voronoi_point( 350, 271, iterate++));
    Game::map[iterate-1].new_neighbor(4);
    Game::map[iterate-1].new_neighbor(6);
    Game::map[iterate-1].new_neighbor(8);
    Game::map.push_back(Voronoi_point( 377, 421, iterate++));
    Game::map[iterate-1].new_neighbor(5);
    Game::map[iterate-1].new_neighbor(7);
    Game::map[iterate-1].new_neighbor(9);
    Game::map.push_back(Voronoi_point( 357, 504, iterate++));
    Game::map[iterate-1].new_neighbor(2);
    Game::map[iterate-1].new_neighbor(6);
    Game::map[iterate-1].new_neighbor(-1);
    Game::map.push_back(Voronoi_point( 544, 309, iterate++));
    Game::map[iterate-1].new_neighbor(5);
    Game::map[iterate-1].new_neighbor(9);
    Game::map[iterate-1].new_neighbor(-1);
    Game::map.push_back(Voronoi_point( 539, 382, iterate++));
    Game::map[iterate-1].new_neighbor(6);
    Game::map[iterate-1].new_neighbor(8);
    Game::map[iterate-1].new_neighbor(10);
    Game::map.push_back(Voronoi_point( 632, 489, iterate++));
    Game::map[iterate-1].new_neighbor(9);
    Game::map[iterate-1].new_neighbor(-1);
    Game::map[iterate-1].new_neighbor(-1);
}

double Game::get_x(short _id)
{
    return map[_id].get_x();
}

double Game::get_y(short _id)
{
    return map[_id].get_y();
}

/*
double Game::get_edge(short _id)
{
    return map[_id].get_edge();
}

double Game::get_harbor(short _id)
{
    return map[_id].get_harbor();
}
*/

short Game::get_neighbour(short _id, short _number)
{
    return map[_id].get_neighbours(_number);
}
