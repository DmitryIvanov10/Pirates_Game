#include "game.h"
#include <QDebug>

Game::Game(QObject *parent) : QObject(parent)
{  
    // randomize in creating all new objects
    std::srand(time(0));

    // amount of NPC in the beginning of the game
    const int start_npc_amount = 3;

    // create map
    new_game();

    // create a scene
    //QGraphicsScene * scene = new QGraphicsScene();

    // create an item to put into the scene
    //Player * player = new Player();
    //rect->setRect(0,0,80,80);
    scene->addItem(player);

    // create npc's to put into the scene
    //NPC * npc_ship1 = new NPC();
    //NPC * npc_ship2 = new NPC();

    // create list to hold NPC ships
    QList<NPC *> npc_ships;

    // create NPCs ships and add them to the list of NPC ships
    for (int i=0; i<start_npc_amount; i++)
    {
        npc_ships << (new NPC());
    }
    //npc_ship->setRect(0,0,20,20);
    /*scene->addItem(npc_ship1);
    scene->addItem(npc_ship2);*/

    // add all NPC ships to the scene
    foreach (NPC * npc_ship, npc_ships)
    {
        scene->addItem(npc_ship);
    }

    // create wind to put into the scene
    //Wind *wind = new Wind();
    scene->addItem(wind);
    //Wind::create_wind();


    // add a view
    //QGraphicsView * view = new QGraphicsView(scene);

    //make item focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // update view
    connect (timer, SIGNAL(timeout()), this, SLOT(center_view()));
    // update player
    connect (timer, SIGNAL(timeout()), player, SLOT(do_tour()));
    // update wind properties
    connect (timer, SIGNAL(timeout()), wind, SLOT(do_tour()));
    /*connect (timer, SIGNAL(timeout()), npc_ship1, SLOT(move_to_next_location()));
    connect (timer, SIGNAL(timeout()), npc_ship2, SLOT(move_to_next_location()));*/

    // update all NPC ships
    foreach (NPC * npc_ship, npc_ships)
    {
        connect (timer, SIGNAL(timeout()), npc_ship, SLOT(move_to_next_location()));
    }

    //view->centerOn(0,0);
    timer->start(17);

    //view->show();
    view->showFullScreen();
   // view->centerOn(player);
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
    // create wind
    Wind::angle = 0;
    Wind::strength = 50;

    short iterate = 1;
    // id = 0
    Game::map.push_back(Voronoi_point(0.0, 0.0, (short)0));
    Game::map[iterate-1].new_neighbor(-1);
    Game::map[iterate-1].new_neighbor(-1);
    Game::map[iterate-1].new_neighbor(-1);
    // id = 1
    Game::map.push_back(Voronoi_point( 123.0, 463.0, iterate++));
    Game::map[iterate-1].new_neighbor(2);
    Game::map[iterate-1].new_neighbor(-1);
    Game::map[iterate-1].new_neighbor(-1);
    // id = 2
    Game::map.push_back(Voronoi_point( 149, 440, iterate++));
    Game::map[iterate-1].new_neighbor(1);
    Game::map[iterate-1].new_neighbor(3);
    Game::map[iterate-1].new_neighbor(7);
    // id = 3
    Game::map.push_back(Voronoi_point( 157,305 , iterate++));
    Game::map[iterate-1].new_neighbor(2);
    Game::map[iterate-1].new_neighbor(4);
    Game::map[iterate-1].new_neighbor(-1);
    // id = 4
    Game::map.push_back(Voronoi_point(259, 107, iterate++));
    Game::map[iterate-1].new_neighbor(3);
    Game::map[iterate-1].new_neighbor(5);
    Game::map[iterate-1].new_neighbor(-1);
    // id = 5
    Game::map.push_back(Voronoi_point( 350, 271, iterate++));
    Game::map[iterate-1].new_neighbor(4);
    Game::map[iterate-1].new_neighbor(6);
    Game::map[iterate-1].new_neighbor(8);
    // id = 6
    Game::map.push_back(Voronoi_point( 377, 421, iterate++));
    Game::map[iterate-1].new_neighbor(5);
    Game::map[iterate-1].new_neighbor(7);
    Game::map[iterate-1].new_neighbor(9);
    // id = 7
    Game::map.push_back(Voronoi_point( 357, 504, iterate++));
    Game::map[iterate-1].new_neighbor(2);
    Game::map[iterate-1].new_neighbor(6);
    Game::map[iterate-1].new_neighbor(-1);
    // id = 8
    Game::map.push_back(Voronoi_point( 544, 309, iterate++));
    Game::map[iterate-1].new_neighbor(5);
    Game::map[iterate-1].new_neighbor(9);
    Game::map[iterate-1].new_neighbor(-1);
    // id = 9
    Game::map.push_back(Voronoi_point( 539, 382, iterate++));
    Game::map[iterate-1].new_neighbor(6);
    Game::map[iterate-1].new_neighbor(8);
    Game::map[iterate-1].new_neighbor(10);
    // id = 10
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

void Game::center_view()
{
    wind->setPos(player->x()-100,player->y()-120);
    view->centerOn(player->get_x(),player->get_y());
}

short Game::get_neighbour(short _id, short _number)
{
    return map[_id].get_neighbour(_number);
}
