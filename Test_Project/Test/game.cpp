#include "game.h"
#include <QDebug>

Game::Game(QObject *parent) : QObject(parent)
{  
    // randomize in creating all new objects
    std::srand(time(0));

    // amount of NPC in the beginning of the game
    const int start_npc_amount = 15;

    // create map
    new_game();

    // create list to hold NPC ships
    QList<NPC *> npc_ships;

    // create NPCs ships and add them to the list of NPC ships
    for (int i=0; i<start_npc_amount; i++)
    {
        npc_ships << (new NPC());
    }

    // add all NPC ships to the scene
    foreach (NPC * npc_ship, npc_ships)
    {
        scene->addItem(npc_ship);
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
    Game::map.push_back(Voronoi_point(785, 1871, ++iterate));
    Game::map[iterate].set_neighbours(2, 14);
    // id = 2
    Game::map.push_back(Voronoi_point(581, 1515, ++iterate));
    Game::map[iterate].set_neighbours(1, 3);
    // id = 3
    Game::map.push_back(Voronoi_point(753, 1339, ++iterate));
    Game::map[iterate].set_neighbours(2, 4, 12);
    // id = 4
    Game::map.push_back(Voronoi_point(395, 994, ++iterate));
    Game::map[iterate].set_neighbours(3, 5);
    // id = 5
    Game::map.push_back(Voronoi_point(721, 782, ++iterate));
    Game::map[iterate].set_neighbours(4, 6, 9);
    // id = 6
    Game::map.push_back(Voronoi_point(395, 493, ++iterate));
    Game::map[iterate].set_neighbours(5, 7);
    // id = 7
    Game::map.push_back(Voronoi_point(629, 307, ++iterate));
    Game::map[iterate].set_neighbours(6, 8);
    // id = 8
    Game::map.push_back(Voronoi_point(891, 403, ++iterate));
    Game::map[iterate].set_neighbours(7, 9, 24);
    // id = 9
    Game::map.push_back(Voronoi_point(816, 775, ++iterate));
    Game::map[iterate].set_neighbours(5, 8, 10);
    // id = 10
    Game::map.push_back(Voronoi_point(1026, 844, ++iterate));
    Game::map[iterate].set_neighbours(9, 11, 22);
    // id = 11
    Game::map.push_back(Voronoi_point(1056, 1216, ++iterate));
    Game::map[iterate].set_neighbours(10, 12, 20);
    // id = 12
    Game::map.push_back(Voronoi_point(968, 1292, ++iterate));
    Game::map[iterate].set_neighbours(3, 11, 13);
    // id = 13
    Game::map.push_back(Voronoi_point(1229, 1681, ++iterate));
    Game::map[iterate].set_neighbours(12, 14, 18);
    // id = 14
    Game::map.push_back(Voronoi_point(1154, 1819, ++iterate));
    Game::map[iterate].set_neighbours(1, 13, 15);
    // id = 15
    Game::map.push_back(Voronoi_point(1357, 1969, ++iterate));
    Game::map[iterate].set_neighbours(14, 16);
    // id = 16
    Game::map.push_back(Voronoi_point(1492, 1939, ++iterate));
    Game::map[iterate].set_neighbours(15, 17, 34);
    // id = 17
    Game::map.push_back(Voronoi_point(1710, 1633, ++iterate));
    Game::map[iterate].set_neighbours(16, 18, 33);
    // id = 18
    Game::map.push_back(Voronoi_point(1566, 1551, ++iterate));
    Game::map[iterate].set_neighbours(13, 17, 19);
    // id = 19
    Game::map.push_back(Voronoi_point(1572, 1301, ++iterate));
    Game::map[iterate].set_neighbours(18, 20, 31);
    // id = 20
    Game::map.push_back(Voronoi_point(1366, 1240, ++iterate));
    Game::map[iterate].set_neighbours(11, 19, 21);
    // id = 21
    Game::map.push_back(Voronoi_point(1517, 762, ++iterate));
    Game::map[iterate].set_neighbours(20, 22, 28);
    // id = 22
    Game::map.push_back(Voronoi_point(1338, 727, ++iterate));
    Game::map[iterate].set_neighbours(10, 21, 23);
    // id = 23
    Game::map.push_back(Voronoi_point(1257, 421, ++iterate));
    Game::map[iterate].set_neighbours(22, 24, 25);
    // id = 24
    Game::map.push_back(Voronoi_point(1068, 362, ++iterate));
    Game::map[iterate].set_neighbours(8, 23);
    // id = 25
    Game::map.push_back(Voronoi_point(1445, 297, ++iterate));
    Game::map[iterate].set_neighbours(23, 26);
    // id = 26
    Game::map.push_back(Voronoi_point(1778, 375, ++iterate));
    Game::map[iterate].set_neighbours(25, 27, 46);
    // id = 27
    Game::map.push_back(Voronoi_point(1788, 584, ++iterate));
    Game::map[iterate].set_neighbours(26, 28, 43);
    // id = 28
    Game::map.push_back(Voronoi_point(1561, 763, ++iterate));
    Game::map[iterate].set_neighbours(21, 27, 29);
    // id = 29
    Game::map.push_back(Voronoi_point(1852, 1012, ++iterate));
    Game::map[iterate].set_neighbours(28, 30, 42);
    // id = 30
    Game::map.push_back(Voronoi_point(1818, 1155, ++iterate));
    Game::map[iterate].set_neighbours(29, 31, 39);
    // id = 31
    Game::map.push_back(Voronoi_point(1773, 1209, ++iterate));
    Game::map[iterate].set_neighbours(19, 30, 32);
    // id = 32
    Game::map.push_back(Voronoi_point(2225, 1611, ++iterate));
    Game::map[iterate].set_neighbours(31, 33, 38);
    // id = 33
    Game::map.push_back(Voronoi_point(2083, 1729, ++iterate));
    Game::map[iterate].set_neighbours(17, 32, 34);
    // id = 34
    Game::map.push_back(Voronoi_point(2053, 1957, ++iterate));
    Game::map[iterate].set_neighbours(16, 33, 35);
    // id = 35
    Game::map.push_back(Voronoi_point(2110, 2083, ++iterate));
    Game::map[iterate].set_neighbours(34, 36);
    // id = 36
    Game::map.push_back(Voronoi_point(2751, 1912, ++iterate));
    Game::map[iterate].set_neighbours(35, 37, 59);
    // id = 37
    Game::map.push_back(Voronoi_point(2736, 1694, ++iterate));
    Game::map[iterate].set_neighbours(36, 38, 56);
    // id = 38
    Game::map.push_back(Voronoi_point(2328, 1570, ++iterate));
    Game::map[iterate].set_neighbours(32, 37, 39);
    // id = 39
    Game::map.push_back(Voronoi_point(2419, 1285, ++iterate));
    Game::map[iterate].set_neighbours(30, 38, 40);
    // id = 40
    Game::map.push_back(Voronoi_point(2469, 1232, ++iterate));
    Game::map[iterate].set_neighbours(39, 41, 55);
    // id = 41
    Game::map.push_back(Voronoi_point(2285, 940, ++iterate));
    Game::map[iterate].set_neighbours(40, 42, 52);
    // id = 42
    Game::map.push_back(Voronoi_point(2149, 917, ++iterate));
    Game::map[iterate].set_neighbours(29, 41, 43);
    // id = 43
    Game::map.push_back(Voronoi_point(2066, 634, ++iterate));
    Game::map[iterate].set_neighbours(27, 42, 44);
    // id = 44
    Game::map.push_back(Voronoi_point(2301, 514, ++iterate));
    Game::map[iterate].set_neighbours(43, 45, 50);
    // id = 45
    Game::map.push_back(Voronoi_point(2257, 368, ++iterate));
    Game::map[iterate].set_neighbours(44, 46, 47);
    // id = 46
    Game::map.push_back(Voronoi_point(1935, 253, ++iterate));
    Game::map[iterate].set_neighbours(26, 45);
    // id = 47
    Game::map.push_back(Voronoi_point(2502, 175, ++iterate));
    Game::map[iterate].set_neighbours(45, 48);
    // id = 48
    Game::map.push_back(Voronoi_point(2620, 254, ++iterate));
    Game::map[iterate].set_neighbours(47, 49, 73);
    // id = 49
    Game::map.push_back(Voronoi_point(2638, 413, ++iterate));
    Game::map[iterate].set_neighbours(48, 50, 71);
    // id = 50
    Game::map.push_back(Voronoi_point(2484, 590, ++iterate));
    Game::map[iterate].set_neighbours(44, 49, 51);
    // id = 51
    Game::map.push_back(Voronoi_point(2540, 657, ++iterate));
    Game::map[iterate].set_neighbours(50, 52, 69);
    // id = 52
    Game::map.push_back(Voronoi_point(2324, 919, ++iterate));
    Game::map[iterate].set_neighbours(41, 51, 53);
    // id = 53
    Game::map.push_back(Voronoi_point(2768, 945, ++iterate));
    Game::map[iterate].set_neighbours(52, 54, 69);
    // id = 54
    Game::map.push_back(Voronoi_point(2863, 1079, ++iterate));
    Game::map[iterate].set_neighbours(53, 55, 65);
    // id = 55
    Game::map.push_back(Voronoi_point(2657, 1203, ++iterate));
    Game::map[iterate].set_neighbours(40, 54, 56);
    // id = 56
    Game::map.push_back(Voronoi_point(3019, 1572, ++iterate));
    Game::map[iterate].set_neighbours(37, 55, 57);
    // id = 57
    Game::map.push_back(Voronoi_point(3173, 1557, ++iterate));
    Game::map[iterate].set_neighbours(56, 58, 64);
    // id = 58
    Game::map.push_back(Voronoi_point(3345, 1818, ++iterate));
    Game::map[iterate].set_neighbours(57, 59, 60);
    // id = 59
    Game::map.push_back(Voronoi_point(2905, 2105, ++iterate));
    Game::map[iterate].set_neighbours(36, 58);
    // id = 60
    Game::map.push_back(Voronoi_point(3509, 1895, ++iterate));
    Game::map[iterate].set_neighbours(58, 61);
    // id = 61
    Game::map.push_back(Voronoi_point(3731, 1826, ++iterate));
    Game::map[iterate].set_neighbours(60, 62);
    // id = 62
    Game::map.push_back(Voronoi_point(3604, 1405, ++iterate));
    Game::map[iterate].set_neighbours(61, 63);
    // id = 63
    Game::map.push_back(Voronoi_point(3478, 1375, ++iterate));
    Game::map[iterate].set_neighbours(62, 64, 84);
    // id = 64
    Game::map.push_back(Voronoi_point(3316, 1405, ++iterate));
    Game::map[iterate].set_neighbours(57, 63, 65);
    // id = 65
    Game::map.push_back(Voronoi_point(3088, 1083, ++iterate));
    Game::map[iterate].set_neighbours(54, 64, 66);
    // id = 66
    Game::map.push_back(Voronoi_point(3303, 836, ++iterate));
    Game::map[iterate].set_neighbours(65, 67, 83);
    // id = 67
    Game::map.push_back(Voronoi_point(3110, 670, ++iterate));
    Game::map[iterate].set_neighbours(66, 68, 78);
    // id = 68
    Game::map.push_back(Voronoi_point(2891, 650, ++iterate));
    Game::map[iterate].set_neighbours(67, 69, 70);
    // id = 69
    Game::map.push_back(Voronoi_point(2738, 697, ++iterate));
    Game::map[iterate].set_neighbours(51, 53, 68);
    // id = 70
    Game::map.push_back(Voronoi_point(2881, 283, ++iterate));
    Game::map[iterate].set_neighbours(68, 71, 76);
    // id = 71
    Game::map.push_back(Voronoi_point(2757, 430, ++iterate));
    Game::map[iterate].set_neighbours(49, 70, 72);
    // id = 72
    Game::map.push_back(Voronoi_point(2824, 377, ++iterate));
    Game::map[iterate].set_neighbours(71, 73, 76);
    // id = 73
    Game::map.push_back(Voronoi_point(2752, 266, ++iterate));
    Game::map[iterate].set_neighbours(48, 72, 74);
    // id = 74
    Game::map.push_back(Voronoi_point(3015, 197, ++iterate));
    Game::map[iterate].set_neighbours(73, 75);
    // id = 75
    Game::map.push_back(Voronoi_point(3093, 289, ++iterate));
    Game::map[iterate].set_neighbours(74, 76, 77);
    // id = 76
    Game::map.push_back(Voronoi_point(2924, 402, ++iterate));
    Game::map[iterate].set_neighbours(70, 72, 75);
    // id = 77
    Game::map.push_back(Voronoi_point(3195, 337, ++iterate));
    Game::map[iterate].set_neighbours(75, 78, 79);
    // id = 78
    Game::map.push_back(Voronoi_point(3225, 448, ++iterate));
    Game::map[iterate].set_neighbours(67, 77, 81);
    // id = 79
    Game::map.push_back(Voronoi_point(3501, 187, ++iterate));
    Game::map[iterate].set_neighbours(77, 80);
    // id = 80
    Game::map.push_back(Voronoi_point(3633, 295, ++iterate));
    Game::map[iterate].set_neighbours(79, 81);
    // id = 81
    Game::map.push_back(Voronoi_point(3584, 495, ++iterate));
    Game::map[iterate].set_neighbours(78, 80, 82);
    // id = 82
    Game::map.push_back(Voronoi_point(3651, 611, ++iterate));
    Game::map[iterate].set_neighbours(81, 83);
    // id = 83
    Game::map.push_back(Voronoi_point(3408, 827, ++iterate));
    Game::map[iterate].set_neighbours(66, 82, 84);
    // id = 84
    Game::map.push_back(Voronoi_point(3663, 991, ++iterate));
    Game::map[iterate].set_neighbours(63, 83);
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
    wind->setPos(player->get_x()-(100 + player->get_width()/2),player->get_y()-(120 + player->get_height()/2));
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
}

short Game::get_neighbour(short _id, short _number)
{
    return map[_id].get_neighbour(_number);
}
