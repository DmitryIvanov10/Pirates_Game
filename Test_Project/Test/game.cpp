#include "game.h"

Game::Game(QObject *parent) : QObject(parent)
{  
    // randomize in creating all new objects
    std::srand(time(0));

    // create map
    new_game();

    // create NPCs ships and add them to the list of NPC ships
    std::vector <NPC *> npc_ships; //statki npc na mapie
    for (int i = 0; i < start_npc_amount; i++)
    {
        npc_ships.push_back(new NPC());
    }

    // add all NPC ships to the scene
    /*
    foreach (NPC * npc_ship, npc_ships)
    {
        scene->addItem(npc_ship);
    }
    */
    for (int i = 0; i < npc_ships.size(); i++)
    {
        scene->addItem(npc_ships[i]);
    }

    // create wind to put into the scene
    scene->addItem(wind);

    //make item focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // update view
    connect (timer, SIGNAL(timeout()), this, SLOT(center_view()));
    // update player
    connect (timer, SIGNAL(timeout()), player, SLOT(do_tour()));
    // update wind properties
    connect (timer, SIGNAL(timeout()), wind, SLOT(do_tour()));

    // update all NPC ships
    foreach (NPC * npc_ship, npc_ships)
    {
        connect (timer, SIGNAL(timeout()), npc_ship, SLOT(move_to_next_location()));
    }

    // put player to the scene
    scene->addItem(player);

    //view->centerOn(0,0);
    timer->start(17);

    //view->show();
    view->showFullScreen();
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

    short iterate = 0;
    // id = 0
    Game::map.push_back(Voronoi_point(0.0, 0.0, (short)0));
    Game::map[0].set_neighbours(-1);
    /*// id = 1
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
    Game::map[iterate-1].new_neighbor(-1);*/


    // id = 1
    Game::map.push_back(Voronoi_point(1570, 3742, ++iterate));
    Game::map[iterate].set_neighbours(2, 14);
    // id = 2
    Game::map.push_back(Voronoi_point(1162, 3030, ++iterate));
    Game::map[iterate].set_neighbours(1, 3);
    // id = 3
    Game::map.push_back(Voronoi_point(1506, 2678, ++iterate));
    Game::map[iterate].set_neighbours(2, 4, 12);
    // id = 4
    Game::map.push_back(Voronoi_point(790, 1988, ++iterate));
    Game::map[iterate].set_neighbours(3, 5);
    // id = 5
    Game::map.push_back(Voronoi_point(1442, 1564, ++iterate));
    Game::map[iterate].set_neighbours(4, 6, 9);
    // id = 6
    Game::map.push_back(Voronoi_point(790, 986, ++iterate));
    Game::map[iterate].set_neighbours(5, 7);
    // id = 7
    Game::map.push_back(Voronoi_point(1258, 614, ++iterate));
    Game::map[iterate].set_neighbours(6, 8);
    // id = 8
    Game::map.push_back(Voronoi_point(1782, 806, ++iterate));
    Game::map[iterate].set_neighbours(7, 9, 24);
    // id = 9
    Game::map.push_back(Voronoi_point(1632, 1550, ++iterate));
    Game::map[iterate].set_neighbours(5, 8, 10);
    // id = 10
    Game::map.push_back(Voronoi_point(2052, 1688, ++iterate));
    Game::map[iterate].set_neighbours(9, 11, 22);
    // id = 11
    Game::map.push_back(Voronoi_point(2112, 2432, ++iterate));
    Game::map[iterate].set_neighbours(10, 12, 20);
    // id = 12
    Game::map.push_back(Voronoi_point(1936, 2584, ++iterate));
    Game::map[iterate].set_neighbours(3, 11, 13);
    // id = 13
    Game::map.push_back(Voronoi_point(2458, 3362, ++iterate));
    Game::map[iterate].set_neighbours(12, 14, 18);
    // id = 14
    Game::map.push_back(Voronoi_point(2308, 3638, ++iterate));
    Game::map[iterate].set_neighbours(1, 13, 15);
    // id = 15
    Game::map.push_back(Voronoi_point(2714, 3938, ++iterate));
    Game::map[iterate].set_neighbours(14, 16);
    // id = 16
    Game::map.push_back(Voronoi_point(2984, 3878, ++iterate));
    Game::map[iterate].set_neighbours(15, 17, 34);
    // id = 17
    Game::map.push_back(Voronoi_point(3420, 3266, ++iterate));
    Game::map[iterate].set_neighbours(16, 18, 33);
    // id = 18
    Game::map.push_back(Voronoi_point(3132, 3102, ++iterate));
    Game::map[iterate].set_neighbours(13, 17, 19);
    // id = 19
    Game::map.push_back(Voronoi_point(3144, 2602, ++iterate));
    Game::map[iterate].set_neighbours(18, 20, 31);
    // id = 20
    Game::map.push_back(Voronoi_point(2732, 2480, ++iterate));
    Game::map[iterate].set_neighbours(11, 19, 21);
    // id = 21
    Game::map.push_back(Voronoi_point(3034, 1524, ++iterate));
    Game::map[iterate].set_neighbours(20, 22, 28);
    // id = 22
    Game::map.push_back(Voronoi_point(2676, 1454, ++iterate));
    Game::map[iterate].set_neighbours(10, 21, 23);
    // id = 23
    Game::map.push_back(Voronoi_point(2514, 842, ++iterate));
    Game::map[iterate].set_neighbours(22, 24, 25);
    // id = 24
    Game::map.push_back(Voronoi_point(2136, 724, ++iterate));
    Game::map[iterate].set_neighbours(8, 23);
    // id = 25
    Game::map.push_back(Voronoi_point(2890, 594, ++iterate));
    Game::map[iterate].set_neighbours(23, 26);
    // id = 26
    Game::map.push_back(Voronoi_point(3556, 750, ++iterate));
    Game::map[iterate].set_neighbours(25, 27, 46);
    // id = 27
    Game::map.push_back(Voronoi_point(3576, 1168, ++iterate));
    Game::map[iterate].set_neighbours(26, 28, 43);
    // id = 28
    Game::map.push_back(Voronoi_point(3122, 1526, ++iterate));
    Game::map[iterate].set_neighbours(21, 27, 29);
    // id = 29
    Game::map.push_back(Voronoi_point(3704, 2024, ++iterate));
    Game::map[iterate].set_neighbours(28, 30, 42);
    // id = 30
    Game::map.push_back(Voronoi_point(3636, 2310, ++iterate));
    Game::map[iterate].set_neighbours(29, 31, 39);
    // id = 31
    Game::map.push_back(Voronoi_point(3546, 2418, ++iterate));
    Game::map[iterate].set_neighbours(19, 30, 32);
    // id = 32
    Game::map.push_back(Voronoi_point(4450, 3222, ++iterate));
    Game::map[iterate].set_neighbours(31, 33, 38);
    // id = 33
    Game::map.push_back(Voronoi_point(4166, 3458, ++iterate));
    Game::map[iterate].set_neighbours(17, 32, 34);
    // id = 34
    Game::map.push_back(Voronoi_point(4106, 3914, ++iterate));
    Game::map[iterate].set_neighbours(16, 33, 35);
    // id = 35
    Game::map.push_back(Voronoi_point(4220, 4166, ++iterate));
    Game::map[iterate].set_neighbours(34, 36);
    // id = 36
    Game::map.push_back(Voronoi_point(5502, 3824, ++iterate));
    Game::map[iterate].set_neighbours(35, 37, 59);
    // id = 37
    Game::map.push_back(Voronoi_point(5472, 3388, ++iterate));
    Game::map[iterate].set_neighbours(36, 38, 56);
    // id = 38
    Game::map.push_back(Voronoi_point(4656, 3140, ++iterate));
    Game::map[iterate].set_neighbours(32, 37, 39);
    // id = 39
    Game::map.push_back(Voronoi_point(4838, 2570, ++iterate));
    Game::map[iterate].set_neighbours(30, 38, 40);
    // id = 40
    Game::map.push_back(Voronoi_point(4938, 2464, ++iterate));
    Game::map[iterate].set_neighbours(39, 41, 55);
    // id = 41
    Game::map.push_back(Voronoi_point(4570, 1880, ++iterate));
    Game::map[iterate].set_neighbours(40, 42, 52);
    // id = 42
    Game::map.push_back(Voronoi_point(4298, 1834, ++iterate));
    Game::map[iterate].set_neighbours(29, 41, 43);
    // id = 43
    Game::map.push_back(Voronoi_point(4132, 1268, ++iterate));
    Game::map[iterate].set_neighbours(27, 42, 44);
    // id = 44
    Game::map.push_back(Voronoi_point(4602, 1028, ++iterate));
    Game::map[iterate].set_neighbours(43, 45, 50);
    // id = 45
    Game::map.push_back(Voronoi_point(4514, 736, ++iterate));
    Game::map[iterate].set_neighbours(44, 46, 47);
    // id = 46
    Game::map.push_back(Voronoi_point(3870, 506, ++iterate));
    Game::map[iterate].set_neighbours(26, 45);
    // id = 47
    Game::map.push_back(Voronoi_point(5004, 350, ++iterate));
    Game::map[iterate].set_neighbours(45, 48);
    // id = 48
    Game::map.push_back(Voronoi_point(5240, 508, ++iterate));
    Game::map[iterate].set_neighbours(47, 49, 73);
    // id = 49
    Game::map.push_back(Voronoi_point(5276, 826, ++iterate));
    Game::map[iterate].set_neighbours(48, 50, 71);
    // id = 50
    Game::map.push_back(Voronoi_point(4968, 1180, ++iterate));
    Game::map[iterate].set_neighbours(44, 49, 51);
    // id = 51
    Game::map.push_back(Voronoi_point(5080, 1314, ++iterate));
    Game::map[iterate].set_neighbours(50, 52, 69);
    // id = 52
    Game::map.push_back(Voronoi_point(4648, 1838, ++iterate));
    Game::map[iterate].set_neighbours(41, 51, 53);
    // id = 53
    Game::map.push_back(Voronoi_point(5536, 1890, ++iterate));
    Game::map[iterate].set_neighbours(52, 54, 69);
    // id = 54
    Game::map.push_back(Voronoi_point(5726, 2158, ++iterate));
    Game::map[iterate].set_neighbours(53, 55, 65);
    // id = 55
    Game::map.push_back(Voronoi_point(5314, 2406, ++iterate));
    Game::map[iterate].set_neighbours(40, 54, 56);
    // id = 56
    Game::map.push_back(Voronoi_point(6038, 3144, ++iterate));
    Game::map[iterate].set_neighbours(37, 55, 57);
    // id = 57
    Game::map.push_back(Voronoi_point(6346, 3114, ++iterate));
    Game::map[iterate].set_neighbours(56, 58, 64);
    // id = 58
    Game::map.push_back(Voronoi_point(6690, 3636, ++iterate));
    Game::map[iterate].set_neighbours(57, 59, 60);
    // id = 59
    Game::map.push_back(Voronoi_point(5810, 4210, ++iterate));
    Game::map[iterate].set_neighbours(36, 58);
    // id = 60
    Game::map.push_back(Voronoi_point(7018, 3790, ++iterate));
    Game::map[iterate].set_neighbours(58, 61);
    // id = 61
    Game::map.push_back(Voronoi_point(7462, 3652, ++iterate));
    Game::map[iterate].set_neighbours(60, 62);
    // id = 62
    Game::map.push_back(Voronoi_point(7208, 2810, ++iterate));
    Game::map[iterate].set_neighbours(61, 63);
    // id = 63
    Game::map.push_back(Voronoi_point(6956, 2750, ++iterate));
    Game::map[iterate].set_neighbours(62, 64, 84);
    // id = 64
    Game::map.push_back(Voronoi_point(6632, 2810, ++iterate));
    Game::map[iterate].set_neighbours(57, 63, 65);
    // id = 65
    Game::map.push_back(Voronoi_point(6176, 2166, ++iterate));
    Game::map[iterate].set_neighbours(54, 64, 66);
    // id = 66
    Game::map.push_back(Voronoi_point(6606, 1672, ++iterate));
    Game::map[iterate].set_neighbours(65, 67, 83);
    // id = 67
    Game::map.push_back(Voronoi_point(6220, 1340, ++iterate));
    Game::map[iterate].set_neighbours(66, 68, 78);
    // id = 68
    Game::map.push_back(Voronoi_point(5782, 1300, ++iterate));
    Game::map[iterate].set_neighbours(67, 69, 70);
    // id = 69
    Game::map.push_back(Voronoi_point(5476, 1394, ++iterate));
    Game::map[iterate].set_neighbours(51, 53, 68);
    // id = 70
    Game::map.push_back(Voronoi_point(5762, 566, ++iterate));
    Game::map[iterate].set_neighbours(68, 71, 76);
    // id = 71
    Game::map.push_back(Voronoi_point(5514, 860, ++iterate));
    Game::map[iterate].set_neighbours(49, 70, 72);
    // id = 72
    Game::map.push_back(Voronoi_point(5648, 754, ++iterate));
    Game::map[iterate].set_neighbours(71, 73, 76);
    // id = 73
    Game::map.push_back(Voronoi_point(5504, 532, ++iterate));
    Game::map[iterate].set_neighbours(48, 72, 74);
    // id = 74
    Game::map.push_back(Voronoi_point(6030, 394, ++iterate));
    Game::map[iterate].set_neighbours(73, 75);
    // id = 75
    Game::map.push_back(Voronoi_point(6186, 578, ++iterate));
    Game::map[iterate].set_neighbours(74, 76, 77);
    // id = 76
    Game::map.push_back(Voronoi_point(5848, 804, ++iterate));
    Game::map[iterate].set_neighbours(70, 72, 75);
    // id = 77
    Game::map.push_back(Voronoi_point(6390, 674, ++iterate));
    Game::map[iterate].set_neighbours(75, 78, 79);
    // id = 78
    Game::map.push_back(Voronoi_point(6450, 896, ++iterate));
    Game::map[iterate].set_neighbours(67, 77, 81);
    // id = 79
    Game::map.push_back(Voronoi_point(7002, 374, ++iterate));
    Game::map[iterate].set_neighbours(77, 80);
    // id = 80
    Game::map.push_back(Voronoi_point(7266, 590, ++iterate));
    Game::map[iterate].set_neighbours(79, 81);
    // id = 81
    Game::map.push_back(Voronoi_point(7168, 990, ++iterate));
    Game::map[iterate].set_neighbours(78, 80, 82);
    // id = 82
    Game::map.push_back(Voronoi_point(7302, 1222, ++iterate));
    Game::map[iterate].set_neighbours(81, 83);
    // id = 83
    Game::map.push_back(Voronoi_point(6816, 1654, ++iterate));
    Game::map[iterate].set_neighbours(66, 82, 84);
    // id = 84
    Game::map.push_back(Voronoi_point(7326, 1982, ++iterate));
    Game::map[iterate].set_neighbours(63, 83);

    //ustawianie kafelków oceanu
    iterate = 0;
    for (int i = -border_y; i < 4608 + border_y; i += 1024)
    for (int j = -border_x; j < 8196 + border_x; j += 1024)
    {
        sea.push_back(new QGraphicsPixmapItem());
        sea[iterate]->setPixmap(QPixmap(":/img/Sea/sea_01.png"));
        scene->addItem(sea[iterate]);
        sea[iterate]->setPos(j, i);
        iterate++;
    }

    //ustawianie wysp
    iterate = 0;
    islands.push_back(new QGraphicsPixmapItem());
    islands[iterate]->setPixmap(QPixmap(":/img/Islands/island_a1_02.png"));
    scene->addItem(islands[iterate]);
    islands[iterate]->setPos(5190, 975);
    iterate++;

    islands.push_back(new QGraphicsPixmapItem());
    islands[iterate]->setPixmap(QPixmap(":/img/Islands/island_a1_01.png"));
    scene->addItem(islands[iterate]);
    islands[iterate]->setPos(3249, 2694);
    iterate++;

    islands.push_back(new QGraphicsPixmapItem());
    islands[iterate]->setPixmap(QPixmap(":/img/Islands/island_a1_03.png"));
    scene->addItem(islands[iterate]);
    islands[iterate]->setPos(2640, 743);
    iterate++;

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
    //wind->setPos(player->get_x()-(100 + player->get_width()/2),player->get_y()-(120 + player->get_height()/2));
    //view->centerOn(player->get_x(),player->get_y());

    if (player->get_x() - scene_x < border_x)
    {
        scene_x = player->get_x() - border_x;
    }
    if (player->get_y() - scene_y < border_y)
    {
        scene_y = player->get_y() - border_y;
    }
    if (scene_x + resolution_x - player->get_x() - player->get_width() < border_x)
    {
        scene_x = player->get_x() + player->get_width() + border_x - resolution_x;
    }
    if (scene_y + resolution_y - player->get_y() - player->get_height() < border_y)
    {
        scene_y = player->get_y() + player->get_height() + border_y - resolution_y;
    }

    scene->setSceneRect(scene_x, scene_y, resolution_x, resolution_y);

    wind->setPos(scene_x, scene_y);
}

short Game::get_neighbour(short _id, short _number)
{
    return map[_id].get_neighbour(_number);
}
