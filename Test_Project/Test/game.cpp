#include "game.h"

Game::Game(QObject *parent) : QObject(parent)
{  
    // randomize in creating all new objects
    std::srand(time(0));

    // create map
    new_game();

    // create NPCs ships and add them to the list of NPC ships
    for (int i = 0; i < start_npc_amount; i++)
    {
        npc_ships.push_back(new NPC());
        scene->addItem(npc_ships[i]);
    }

    // create wind to put into the scene
    //aktualnie wiatr jest na scenie nie potrzebny, zawsze można go dodać
    //scene->addItem(wind);

    //make item focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // update all NPC ships
    foreach (NPC * npc_ship, npc_ships)
    {
        connect (timer, SIGNAL(timeout()), npc_ship, SLOT(move_to_next_location()));
        scene->addItem(npc_ship->flag);
    }

    //make HUD
    set_hud();

    // update all elements' states
    connect (timer, SIGNAL(timeout()), this, SLOT(update_states()));
    // update view
    connect (timer, SIGNAL(timeout()), this, SLOT(center_view()));
    // update player
    connect (timer, SIGNAL(timeout()), player, SLOT(do_tour()));
    // update wind properties
    connect (timer, SIGNAL(timeout()), wind, SLOT(do_tour()));
    // set new day in the game
    connect (timer, SIGNAL(timeout()), this, SLOT(count_days()));
    // update player properties each new day
    connect (this, SIGNAL(new_day()), player, SLOT(next_day()));
    // ruchy myszki
    connect (view, SIGNAL(mouse_moved()), this, SLOT(mouse_moved()));

    connect(player, SIGNAL(start_battle(Ship*)), this, SLOT(start_player_battle(Ship*)));    

    // put player to the scene
    scene->addItem(player);

    scene->addItem(player->probe);

    //set timer to achieve 60 FPS
    timer->start(17);

    // show game on a full screen
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
    Voronoi_points::map.push_back(Voronoi_point(0.0, 0.0, (short)0));
    Voronoi_points::map[0].set_neighbours(-1);
    // id = 1
    Voronoi_points::map.push_back(Voronoi_point(1570, 3742, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(2, 14);
    // id = 2
    Voronoi_points::map.push_back(Voronoi_point(1162, 3030, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(1, 3);
    // id = 3
    Voronoi_points::map.push_back(Voronoi_point(1506, 2678, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(2, 4, 12);
    // id = 4
    Voronoi_points::map.push_back(Voronoi_point(790, 1988, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(3, 5);
    // id = 5
    Voronoi_points::map.push_back(Voronoi_point(1442, 1564, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(4, 6, 9);
    // id = 6
    Voronoi_points::map.push_back(Voronoi_point(790, 986, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(5, 7);
    // id = 7
    Voronoi_points::map.push_back(Voronoi_point(1258, 614, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(6, 8);
    // id = 8
    Voronoi_points::map.push_back(Voronoi_point(1782, 806, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(7, 9, 24);
    // id = 9
    Voronoi_points::map.push_back(Voronoi_point(1632, 1550, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(5, 8, 10);
    // id = 10
    Voronoi_points::map.push_back(Voronoi_point(2052, 1688, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(9, 11, 22);
    // id = 11
    Voronoi_points::map.push_back(Voronoi_point(2112, 2432, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(10, 12, 20);
    // id = 12
    Voronoi_points::map.push_back(Voronoi_point(1936, 2584, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(3, 11, 13);
    // id = 13
    Voronoi_points::map.push_back(Voronoi_point(2458, 3362, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(12, 14, 18);
    // id = 14
    Voronoi_points::map.push_back(Voronoi_point(2308, 3638, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(1, 13, 15);
    // id = 15
    Voronoi_points::map.push_back(Voronoi_point(2714, 3938, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(14, 16);
    // id = 16
    Voronoi_points::map.push_back(Voronoi_point(2984, 3878, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(15, 17, 34);
    // id = 17
    Voronoi_points::map.push_back(Voronoi_point(3420, 3266, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(16, 18, 33);
    // id = 18
    Voronoi_points::map.push_back(Voronoi_point(3132, 3102, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(13, 17, 19);
    // id = 19
    Voronoi_points::map.push_back(Voronoi_point(3144, 2602, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(18, 20, 31);
    // id = 20
    Voronoi_points::map.push_back(Voronoi_point(2732, 2480, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(11, 19, 21);
    // id = 21
    Voronoi_points::map.push_back(Voronoi_point(3034, 1524, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(20, 22, 28);
    // id = 22
    Voronoi_points::map.push_back(Voronoi_point(2676, 1454, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(10, 21, 23);
    // id = 23
    Voronoi_points::map.push_back(Voronoi_point(2514, 842, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(22, 24, 25);
    // id = 24
    Voronoi_points::map.push_back(Voronoi_point(2136, 724, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(8, 23);
    // id = 25
    Voronoi_points::map.push_back(Voronoi_point(2890, 594, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(23, 26);
    // id = 26
    Voronoi_points::map.push_back(Voronoi_point(3556, 750, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(25, 27, 46);
    // id = 27
    Voronoi_points::map.push_back(Voronoi_point(3576, 1168, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(26, 28, 43);
    // id = 28
    Voronoi_points::map.push_back(Voronoi_point(3122, 1526, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(21, 27, 29);
    // id = 29
    Voronoi_points::map.push_back(Voronoi_point(3704, 2024, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(28, 30, 42);
    // id = 30
    Voronoi_points::map.push_back(Voronoi_point(3636, 2310, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(29, 31, 39);
    // id = 31
    Voronoi_points::map.push_back(Voronoi_point(3546, 2418, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(19, 30, 32);
    // id = 32
    Voronoi_points::map.push_back(Voronoi_point(4450, 3222, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(31, 33, 38);
    // id = 33
    Voronoi_points::map.push_back(Voronoi_point(4166, 3458, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(17, 32, 34);
    // id = 34
    Voronoi_points::map.push_back(Voronoi_point(4106, 3914, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(16, 33, 35);
    // id = 35
    Voronoi_points::map.push_back(Voronoi_point(4220, 4166, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(34, 36);
    // id = 36
    Voronoi_points::map.push_back(Voronoi_point(5502, 3824, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(35, 37, 59);
    // id = 37
    Voronoi_points::map.push_back(Voronoi_point(5472, 3388, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(36, 38, 56);
    // id = 38
    Voronoi_points::map.push_back(Voronoi_point(4656, 3140, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(32, 37, 39);
    // id = 39
    Voronoi_points::map.push_back(Voronoi_point(4838, 2570, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(30, 38, 40);
    // id = 40
    Voronoi_points::map.push_back(Voronoi_point(4938, 2464, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(39, 41, 55);
    // id = 41
    Voronoi_points::map.push_back(Voronoi_point(4570, 1880, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(40, 42, 52);
    // id = 42
    Voronoi_points::map.push_back(Voronoi_point(4298, 1834, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(29, 41, 43);
    // id = 43
    Voronoi_points::map.push_back(Voronoi_point(4132, 1268, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(27, 42, 44);
    // id = 44
    Voronoi_points::map.push_back(Voronoi_point(4602, 1028, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(43, 45, 50);
    // id = 45
    Voronoi_points::map.push_back(Voronoi_point(4514, 736, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(44, 46, 47);
    // id = 46
    Voronoi_points::map.push_back(Voronoi_point(3870, 506, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(26, 45);
    // id = 47
    Voronoi_points::map.push_back(Voronoi_point(5004, 350, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(45, 48);
    // id = 48
    Voronoi_points::map.push_back(Voronoi_point(5240, 508, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(47, 49, 73);
    // id = 49
    Voronoi_points::map.push_back(Voronoi_point(5276, 826, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(48, 50, 71);
    // id = 50
    Voronoi_points::map.push_back(Voronoi_point(4968, 1180, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(44, 49, 51);
    // id = 51
    Voronoi_points::map.push_back(Voronoi_point(5080, 1314, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(50, 52, 69);
    // id = 52
    Voronoi_points::map.push_back(Voronoi_point(4648, 1838, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(41, 51, 53);
    // id = 53
    Voronoi_points::map.push_back(Voronoi_point(5536, 1890, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(52, 54, 69);
    // id = 54
    Voronoi_points::map.push_back(Voronoi_point(5726, 2158, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(53, 55, 65);
    // id = 55
    Voronoi_points::map.push_back(Voronoi_point(5314, 2406, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(40, 54, 56);
    // id = 56
    Voronoi_points::map.push_back(Voronoi_point(6038, 3144, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(37, 55, 57);
    // id = 57
    Voronoi_points::map.push_back(Voronoi_point(6346, 3114, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(56, 58, 64);
    // id = 58
    Voronoi_points::map.push_back(Voronoi_point(6690, 3636, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(57, 59, 60);
    // id = 59
    Voronoi_points::map.push_back(Voronoi_point(5810, 4210, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(36, 58);
    // id = 60
    Voronoi_points::map.push_back(Voronoi_point(7018, 3790, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(58, 61);
    // id = 61
    Voronoi_points::map.push_back(Voronoi_point(7462, 3652, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(60, 62);
    // id = 62
    Voronoi_points::map.push_back(Voronoi_point(7208, 2810, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(61, 63);
    // id = 63
    Voronoi_points::map.push_back(Voronoi_point(6956, 2750, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(62, 64, 84);
    // id = 64
    Voronoi_points::map.push_back(Voronoi_point(6632, 2810, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(57, 63, 65);
    // id = 65
    Voronoi_points::map.push_back(Voronoi_point(6176, 2166, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(54, 64, 66);
    // id = 66
    Voronoi_points::map.push_back(Voronoi_point(6606, 1672, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(65, 67, 83);
    // id = 67
    Voronoi_points::map.push_back(Voronoi_point(6220, 1340, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(66, 68, 78);
    // id = 68
    Voronoi_points::map.push_back(Voronoi_point(5782, 1300, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(67, 69, 70);
    // id = 69
    Voronoi_points::map.push_back(Voronoi_point(5476, 1394, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(51, 53, 68);
    // id = 70
    Voronoi_points::map.push_back(Voronoi_point(5762, 566, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(68, 71, 76);
    // id = 71
    Voronoi_points::map.push_back(Voronoi_point(5514, 860, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(49, 70, 72);
    // id = 72
    Voronoi_points::map.push_back(Voronoi_point(5648, 754, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(71, 73, 76);
    // id = 73
    Voronoi_points::map.push_back(Voronoi_point(5504, 532, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(48, 72, 74);
    // id = 74
    Voronoi_points::map.push_back(Voronoi_point(6030, 394, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(73, 75);
    // id = 75
    Voronoi_points::map.push_back(Voronoi_point(6186, 578, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(74, 76, 77);
    // id = 76
    Voronoi_points::map.push_back(Voronoi_point(5848, 804, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(70, 72, 75);
    // id = 77
    Voronoi_points::map.push_back(Voronoi_point(6390, 674, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(75, 78, 79);
    // id = 78
    Voronoi_points::map.push_back(Voronoi_point(6450, 896, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(67, 77, 81);
    // id = 79
    Voronoi_points::map.push_back(Voronoi_point(7002, 374, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(77, 80);
    // id = 80
    Voronoi_points::map.push_back(Voronoi_point(7266, 590, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(79, 81);
    // id = 81
    Voronoi_points::map.push_back(Voronoi_point(7168, 990, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(78, 80, 82);
    // id = 82
    Voronoi_points::map.push_back(Voronoi_point(7302, 1222, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(81, 83);
    // id = 83
    Voronoi_points::map.push_back(Voronoi_point(6816, 1654, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(66, 82, 84);
    // id = 84
    Voronoi_points::map.push_back(Voronoi_point(7326, 1982, ++iterate));
    Voronoi_points::map[iterate].set_neighbours(63, 83);

    //ustawianie kafelków oceanu
    /*iterate = 0;
    for (int i = -border_y; i < 4608 + border_y; i += 1024)
    for (int j = -border_x; j < 8196 + border_x; j += 1024)
    {
        sea.push_back(new QGraphicsPixmapItem());
        sea[iterate]->setPixmap(QPixmap(":/img/Sea/sea_01.png"));
        scene->addItem(sea[iterate]);
        sea[iterate]->setPos(j, i);
        iterate++;
    }*/
    scene->setBackgroundBrush(QBrush(QImage(":/img/Sea/sea_01.png")));

    //ustawianie wysp
    set_island(5190, 975, ":/island_a1_02.png");
    set_island(3249, 2694, ":/island_a1_01.png");
    set_island(6096, 3829, ":/island_a1_03.png");
    set_island(1848, 874, ":/island_a2_02.png");
    set_island(4852, 2558, ":/island_a3_02.png");
    set_island(411, 2175, ":/island_a3_02.png");
    set_island(4253, 3325, ":/island_a2_03.png");
    set_island(5583, 1386, ":/island_a4_01.png");
    set_island(1629, 3737, ":/island_a4_02.png");
}

double Game::get_x(short _id)
{
    return Voronoi_points::map[_id].get_x();
}

double Game::get_y(short _id)
{
    return Voronoi_points::map[_id].get_y();
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

void Game::count_days()
{
    game_time ++;
    if (game_time > game_day)
    {
        game_time = 0;
        emit new_day();
    }
}

void Game::update_states()
{
    foreach (NPC* ship, npc_ships)
    {
        if (ship->get_x() > scene_x &&
            ship->get_x() < scene_x + resolution_x &&
            ship->get_y() > scene_y &&
            ship->get_y() < scene_y + resolution_y)
        {
            ship->set_state(true);
        } else
        {
            ship->set_state(false);
        }
    }
    foreach (Island* island, islands)
    {
        if (island->get_x() > scene_x - 1000 &&
            island->get_x() < scene_x + resolution_x &&
            island->get_y() > scene_y - 1000 &&
            island->get_y() < scene_y + resolution_y)
        {
            island->set_state(true);
        } else
        {
            island->set_state(false);
        }
    }
}

void Game::center_view()
{
    player->setFocus();

    if (player->get_x() - scene_x < border_x)
    {
        scene_x = (int)player->get_x() - border_x;
    }
    if (player->get_y() - scene_y < border_y)
    {
        scene_y = (int)player->get_y() - border_y;
    }
    if (scene_x + resolution_x - player->get_x() - player->get_sprite_width() < border_x)
    {
        scene_x = (int)player->get_x() + player->get_sprite_width() + border_x - resolution_x;
    }
    if (scene_y + resolution_y - player->get_y() - player->get_sprite_height() < border_y)
    {
        scene_y = (int)player->get_y() + player->get_sprite_height() + border_y - resolution_y;
    }

    scene->setSceneRect(scene_x, scene_y, resolution_x, resolution_y);

    wind->setPos(scene_x, scene_y);

    hud_img[0]->setPos(scene_x + resolution_x - hud_img[0]->pixmap().width(),
            scene_y + resolution_y - hud_img[0]->pixmap().height());
    hud_img[1]->setPos(scene_x + resolution_x - hud_img[1]->pixmap().width(), scene_y - 2);
    hud_img[2]->setPos(scene_x + resolution_x/2 - hud_img[2]->pixmap().width()/2, scene_y - 2);
    hud_img[3]->setPos(scene_x + resolution_x/2 - hud_img[3]->pixmap().width()/2,
            scene_y + resolution_y - hud_img[3]->pixmap().height());
    hud_img[4]->setPos(scene_x, scene_y + resolution_y - hud_img[4]->pixmap().height());
    hud_img[5]->setPos(scene_x,scene_y);

    hud_img[6]->setTransformOriginPoint(50, 50);
    hud_img[6]->setRotation(-1 * Wind::angle);
    hud_img[6]->setPos(scene_x + resolution_x - 125, scene_y + resolution_y - 125);

    switch (player->get_sail_level())
    {
        case 0:
            hud_img[7]->setPixmap(QPixmap(":/img/Interface/Sails/sail_none_01.png"));
            break;
        case 1:
            hud_img[7]->setPixmap(QPixmap(":/img/Interface/Sails/sail_half_01.png"));
            break;
        case 2:
            hud_img[7]->setPixmap(QPixmap(":/img/Interface/Sails/sail_full_01.png"));
            break;
    }
    hud_img[7]->setPos(scene_x + resolution_x - hud_img[7]->pixmap().width(),
            scene_y + resolution_y - hud_img[7]->pixmap().height() - hud_img[0]->pixmap().height() + 108);

    //siła wiatru
    hud_txt[0]->setPlainText(QString(QString::number(Wind::strength)));
    hud_txt[0]->setPos(scene_x + resolution_x - 182, scene_y + resolution_y - 47);

    //zdrowie statku
    hud_txt[1]->setPlainText(QString(QString::number(player->get_health())));
    hud_txt[1]->setPos(scene_x + resolution_x/2 - 222, scene_y + resolution_y - 40);

    //stan załogi
    hud_txt[2]->setPlainText(QString(QString::number(player->get_crew())));
    hud_txt[2]->setPos(scene_x + resolution_x/2 - 134, scene_y + resolution_y - 40);

    //ilość jedzenia
    hud_txt[3]->setPlainText(QString(QString::number(player->get_food())));
    hud_txt[3]->setPos(scene_x + resolution_x/2 - 53, scene_y + resolution_y - 40);

    //ilość stan morale
    hud_txt[4]->setPlainText(QString(QString::number(player->get_morale())));
    hud_txt[4]->setPos(scene_x + resolution_x/2 + 34, scene_y + resolution_y - 40);

    //ilość armat
    hud_txt[5]->setPlainText(QString(QString::number(player->get_cannons())));
    hud_txt[5]->setPos(scene_x + resolution_x - 75, scene_y + 31);

    //ilość amunicji
    hud_txt[6]->setPlainText(QString(QString::number(player->get_ammo())));
    hud_txt[6]->setPos(scene_x + resolution_x - 75, scene_y + 59);

    //ilość złota
    hud_txt[7]->setPlainText(QString(QString::number(player->get_gold())));
    hud_txt[7]->setPos(scene_x + resolution_x/2 + 121, scene_y + resolution_y - 40);

    //tekst menu
    hud_txt[8]->setPos(scene_x + 45, scene_y + 10);

    //elementy tymczasowe


    //stan zdrowia
    if (hud_temp_bool[0])
    {
        hud_temp_img[0]->setPos(scene_x + resolution_x/2 - 220, scene_y + resolution_y - 134);
        hud_temp_txt[0]->setPos(scene_x + resolution_x/2 - 220, scene_y + resolution_y - 134);
    }
    else
    {
        hud_temp_img[0]->setPos(0,0);
        hud_temp_txt[0]->setPos(0,0);
    }

    //stan załogi
    if (hud_temp_bool[1])
    {
        hud_temp_img[1]->setPos(scene_x + resolution_x/2 - 132, scene_y + resolution_y - 134);
        hud_temp_txt[1]->setPos(scene_x + resolution_x/2 - 132, scene_y + resolution_y - 134);
    }
    else
    {
        hud_temp_img[1]->setPos(0,0);
        hud_temp_txt[1]->setPos(0,0);
    }

    //stan jedzenia
    if (hud_temp_bool[2])
    {
        hud_temp_img[2]->setPos(scene_x + resolution_x/2 - 51, scene_y + resolution_y - 134);
        hud_temp_txt[2]->setPos(scene_x + resolution_x/2 - 51, scene_y + resolution_y - 134);
    }
    else
    {
        hud_temp_img[2]->setPos(0,0);
        hud_temp_txt[2]->setPos(0,0);
    }

    //stan morale
    if (hud_temp_bool[3])
    {
        hud_temp_img[3]->setPos(scene_x + resolution_x/2 + 37, scene_y + resolution_y - 134);
        hud_temp_txt[3]->setPos(scene_x + resolution_x/2 + 37, scene_y + resolution_y - 134);
    }
    else
    {
        hud_temp_img[3]->setPos(0,0);
        hud_temp_txt[3]->setPos(0,0);
    }

    //stan złota
    if (hud_temp_bool[4])
    {
        hud_temp_img[4]->setPos(scene_x + resolution_x/2 + 124, scene_y + resolution_y - 134);
        hud_temp_txt[4]->setPos(scene_x + resolution_x/2 + 124, scene_y + resolution_y - 134);
    }
    else
    {
        hud_temp_img[4]->setPos(0,0);
        hud_temp_txt[4]->setPos(0,0);
    }

    //inne elementy HUD'u
    map_rect->setRect(scene_x + 15 + 265 * ((float)scene_x / (8196 + 2 * border_x)), scene_y + resolution_y - 156 + 148 * ((float)scene_y / (4608 + 2* border_y)), (int)(267 * ((float)resolution_x / (8196 + 2* border_x))), (int)(151 * ((float)resolution_y / (4608 + 2* border_y))));
}

void Game::start_player_battle(Ship *_ship)
{
    start_stop();

    battles.push_back(new Battle(player, _ship));
    connect(battles[battles.size()-1], SIGNAL(finish_battle()), this, SLOT(reset_timer()));
}

short Game::get_neighbour(short _id, short _number)
{
    return Voronoi_points::map[_id].get_neighbour(_number);
}

void Game::set_hud()
{
    //elementy graficzne
    int iterate = 0;

    //HUD dotyczący ruchu w prawym dolnym rogu
    hud_img.push_back(new QGraphicsPixmapItem());
    hud_img[iterate]->setPixmap(QPixmap(":/img/Interface/HUD/Interface_PD_02.png"));
    scene->addItem(hud_img[iterate]);
    //hud_img[iterate]->setPos(scene_x + resolution_x - hud_img[iterate]->pixmap().width(), scene_y + resolution_y - hud_img[iterate]->pixmap().height());
    iterate++;

    //HUD dotyczący stanu statku w prawym górnym rogu
    hud_img.push_back(new QGraphicsPixmapItem());
    hud_img[iterate]->setPixmap(QPixmap(":/img/Interface/HUD/Interface_PG_02.png"));
    scene->addItem(hud_img[iterate]);
    //hud_img[iterate]->setPos(scene_x + resolution_x - 220, scene_y - 2);
    iterate++;

    //HUD dotyczący stanu ładowni po środku na górze
    hud_img.push_back(new QGraphicsPixmapItem());
    hud_img[iterate]->setPixmap(QPixmap(":/Interface_SG_03.png"));
    scene->addItem(hud_img[iterate]);
    //hud_img[iterate]->setPos(scene_x + resolution_x/2 - 350, scene_y - 2);
    iterate++;

    //HUD dotyczący stanu załogi i pieniędzy po środku na dole
    hud_img.push_back(new QGraphicsPixmapItem());
    hud_img[iterate]->setPixmap(QPixmap(":/Interface_SD_03.png"));
    scene->addItem(hud_img[iterate]);
    //hud_img[iterate]->setPos(scene_x + resolution_x/2 - 225, scene_y + resolution_y - 49);
    iterate++;

    //HUD z mapą w lewym dolnym rogu
    hud_img.push_back(new QGraphicsPixmapItem());
    hud_img[iterate]->setPixmap(QPixmap(":/img/Interface/HUD/Interface_LD_02.png"));
    scene->addItem(hud_img[iterate]);
    //hud_img[iterate]->setPos(scene_x, scene_y + resolution_y - 219);
    iterate++;

    //HUD w lewym górnym rogu
    hud_img.push_back(new QGraphicsPixmapItem());
    hud_img[iterate]->setPixmap(QPixmap(":/interface_LG_01.png"));
    scene->addItem(hud_img[iterate]);
    iterate++;

    //strzałka wiatru
    hud_img.push_back(new QGraphicsPixmapItem());
    hud_img[iterate]->setPixmap(QPixmap(":/img/Interface/HUD/arrow_02.png"));
    scene->addItem(hud_img[iterate]);
    //hud_img[iterate]->setPos(scene_x + resolution_x - 125, scene_y + resolution_y - 125);
    iterate++;

    //stan zagli
    hud_img.push_back(new QGraphicsPixmapItem());
    hud_img[iterate]->setPixmap(QPixmap(":/img/Interface/Sails/sail_half_01.png"));
    scene->addItem(hud_img[iterate]);
    //hud_img[iterate]->setPos(scene_x + resolution_x - 125, scene_y + resolution_y - 125);
    //iterate++;

    //elementy tekstowe
    iterate = 0;

    //siła wiatru
    hud_txt.push_back(new QGraphicsTextItem());
    hud_txt[iterate]->setPlainText(QString(QString::number(Wind::strength)));
    hud_txt[iterate]->setFont(QFont("times", 20));
    scene->addItem(hud_txt[iterate]);
    //hud_txt[iterate]->setPos(scene_x + resolution_x - 181, scene_y + resolution_y - 47);
    iterate++;

    //zdrowie statku
    hud_txt.push_back(new QGraphicsTextItem());
    hud_txt[iterate]->setPlainText(QString(QString::number(player->get_health())));
    hud_txt[iterate]->setFont(QFont("times", 13));
    scene->addItem(hud_txt[iterate]);
    //hud_txt[iterate]->setPos(scene_x + resolution_x/2 - 189, scene_y + resolution_y - 36);
    iterate++;

    //stan załogi
    hud_txt.push_back(new QGraphicsTextItem());
    hud_txt[iterate]->setPlainText(QString(QString::number(player->get_crew())));
    hud_txt[iterate]->setFont(QFont("times", 13));
    scene->addItem(hud_txt[iterate]);
    //hud_txt[iterate]->setPos(scene_x + resolution_x/2 - 111, scene_y + resolution_y - 36);
    iterate++;

    //ilość jedzenia
    hud_txt.push_back(new QGraphicsTextItem());
    hud_txt[iterate]->setPlainText(QString(QString::number(player->get_food())));
    hud_txt[iterate]->setFont(QFont("times", 13));
    scene->addItem(hud_txt[iterate]);
    //hud_txt[iterate]->setPos(scene_x + resolution_x/2 - 45, scene_y + resolution_y - 36);
    iterate++;

    //stan morale
    hud_txt.push_back(new QGraphicsTextItem());
    hud_txt[iterate]->setPlainText(QString(QString::number(player->get_morale())));
    hud_txt[iterate]->setFont(QFont("times", 13));
    scene->addItem(hud_txt[iterate]);
    //hud_txt[iterate]->setPos(scene_x + resolution_x/2 + 31, scene_y + resolution_y - 36);
    iterate++;

    //ilość armat
    hud_txt.push_back(new QGraphicsTextItem());
    hud_txt[iterate]->setPlainText(QString(QString::number(player->get_cannons())));
    hud_txt[iterate]->setFont(QFont("times", 13));
    scene->addItem(hud_txt[iterate]);
    //hud_txt[iterate]->setPos(scene_x + resolution_x - 75, scene_y + 31);
    iterate++;

    //ilość amunicji
    hud_txt.push_back(new QGraphicsTextItem());
    hud_txt[iterate]->setPlainText(QString(QString::number(player->get_ammo())));
    hud_txt[iterate]->setFont(QFont("times", 13));
    scene->addItem(hud_txt[iterate]);
    //hud_txt[iterate]->setPos(scene_x + resolution_x - 75, scene_y + 59);
    iterate++;

    //ilość złota
    hud_txt.push_back(new QGraphicsTextItem());
    hud_txt[iterate]->setPlainText(QString(QString::number(player->get_gold())));
    hud_txt[iterate]->setFont(QFont("times", 13));
    scene->addItem(hud_txt[iterate]);
    iterate++;

    //tekst menu
    hud_txt.push_back(new QGraphicsTextItem());
    hud_txt[iterate]->setPlainText(QString("MENU"));
    hud_txt[iterate]->setFont(QFont("times", 16));
    scene->addItem(hud_txt[iterate]);
    iterate++;

    //elementy graficzne tymczasowe, odpowiadające im elementy tekstowe i bool'owskie
    iterate = 0;

    //stan zdrowia
    hud_temp_img.push_back(new QGraphicsPixmapItem());
    hud_temp_img[iterate]->setPixmap(QPixmap(":/temp_health_01.png"));
    scene->addItem(hud_temp_img[iterate]);
    //hud_temp_img[iterate]->setPos(0,0);

    hud_temp_txt.push_back(new QGraphicsTextItem());
    hud_temp_txt[iterate]->setPlainText(QString("Health"));
    hud_temp_txt[iterate]->setFont(QFont("times", 13));
    scene->addItem(hud_temp_txt[iterate]);
    //hud_temp_txt[iterate]->setPos(0,0);

    hud_temp_bool.push_back(0);
    iterate++;

    //stan załogi
    hud_temp_img.push_back(new QGraphicsPixmapItem());
    hud_temp_img[iterate]->setPixmap(QPixmap(":/temp_crue_01.png"));
    scene->addItem(hud_temp_img[iterate]);
    //hud_temp_img[iterate]->setPos(0,0);

    hud_temp_txt.push_back(new QGraphicsTextItem());
    hud_temp_txt[iterate]->setPlainText(QString("Crue"));
    hud_temp_txt[iterate]->setFont(QFont("times", 13));
    scene->addItem(hud_temp_txt[iterate]);
    //hud_temp_txt[iterate]->setPos(0,0);

    hud_temp_bool.push_back(0);
    iterate++;

    //stan jedzenia
    hud_temp_img.push_back(new QGraphicsPixmapItem());
    hud_temp_img[iterate]->setPixmap(QPixmap(":/temp_food_01.png"));
    scene->addItem(hud_temp_img[iterate]);
    //hud_temp_img[iterate]->setPos(0,0);

    hud_temp_txt.push_back(new QGraphicsTextItem());
    hud_temp_txt[iterate]->setPlainText(QString("Food"));
    hud_temp_txt[iterate]->setFont(QFont("times", 13));
    scene->addItem(hud_temp_txt[iterate]);
    //hud_temp_txt[iterate]->setPos(0,0);

    hud_temp_bool.push_back(0);
    iterate++;

    //stan morale
    hud_temp_img.push_back(new QGraphicsPixmapItem());
    hud_temp_img[iterate]->setPixmap(QPixmap(":/temp_morale_01.png"));
    scene->addItem(hud_temp_img[iterate]);
    //hud_temp_img[iterate]->setPos(0,0);

    hud_temp_txt.push_back(new QGraphicsTextItem());
    hud_temp_txt[iterate]->setPlainText(QString("Morale"));
    hud_temp_txt[iterate]->setFont(QFont("times", 13));
    scene->addItem(hud_temp_txt[iterate]);
    //hud_temp_txt[iterate]->setPos(0,0);

    hud_temp_bool.push_back(0);
    iterate++;

    //stan złota
    hud_temp_img.push_back(new QGraphicsPixmapItem());
    hud_temp_img[iterate]->setPixmap(QPixmap(":/temp_gold_01.png"));
    scene->addItem(hud_temp_img[iterate]);
    //hud_temp_img[iterate]->setPos(0,0);

    hud_temp_txt.push_back(new QGraphicsTextItem());
    hud_temp_txt[iterate]->setPlainText(QString("Gold"));
    hud_temp_txt[iterate]->setFont(QFont("times", 13));
    scene->addItem(hud_temp_txt[iterate]);
    //hud_temp_txt[iterate]->setPos(0,0);

    hud_temp_bool.push_back(0);
    iterate++;


    //Prostokącik na mapie
    map_rect = new QGraphicsRectItem();
    //map_rect->setRect(scene_x + 15 + 265 * ((float)scene_x / (8196 + 2 * border_x)), scene_y + resolution_y - 156 + 148 * ((float)scene_y / (4608 + 2* border_y)), (int)(267 * ((float)resolution_x / (8196 + 2* border_x))), (int)(151 * ((float)resolution_y / (4608 + 2* border_y))));
    scene->addItem(map_rect);
}

void Game::set_island(short _x, short _y, QString _pixmap_name)
{
    islands.push_back(new Island());
    islands[islands.size() - 1]->setPixmap(QPixmap(_pixmap_name));
    scene->addItem(islands[islands.size() - 1]);
    islands[islands.size() - 1]->setPos(_x, _y);
    Player::island_coordinates.push_back(islands[islands.size() - 1]->pos());
}

void Game::start_stop()
{
    if (pause)
        timer->start(frame_time);
    else
        timer->stop();
    pause = !pause;
}

void Game::mouse_moved()
{
    //obszar z ikoną zdrowia
    if (view->get_x() > resolution_x/2 - 220 && view->get_x() < resolution_x/2 - 100 && view->get_y() < resolution_y - 10 && view->get_y() > resolution_y - 38)
        hud_temp_bool[0] = 1;
    if (!(view->get_x() > resolution_x/2 - 220 && view->get_x() < resolution_x/2 - 150 && view->get_y() < resolution_y - 10 && view->get_y() > resolution_y - 38))
        hud_temp_bool[0] = 0;

    //obszar z ikoną załogi
    if (view->get_x() > resolution_x/2 - 132 && view->get_x() < resolution_x/2 -50 && view->get_y() < resolution_y - 10 && view->get_y() > resolution_y - 38)
        hud_temp_bool[1] = 1;
    if (!(view->get_x() > resolution_x/2 - 132 && view->get_x() < resolution_x/2 -50 && view->get_y() < resolution_y - 10 && view->get_y() > resolution_y - 38))
        hud_temp_bool[1] = 0;

    //obszar z ikoną jedzenia
    if (view->get_x() > resolution_x/2 - 51 && view->get_x() < resolution_x/2 +20 && view->get_y() < resolution_y - 10 && view->get_y() > resolution_y - 38)
        hud_temp_bool[2] = 1;
    if (!(view->get_x() > resolution_x/2 -51  && view->get_x() < resolution_x/2 +20 && view->get_y() < resolution_y - 10 && view->get_y() > resolution_y - 38))
        hud_temp_bool[2] = 0;

    //obszar z ikoną morale
    if (view->get_x() > resolution_x/2 + 37 && view->get_x() < resolution_x/2 +80 && view->get_y() < resolution_y - 10 && view->get_y() > resolution_y - 38)
        hud_temp_bool[3] = 1;
    if (!(view->get_x() > resolution_x/2 +37  && view->get_x() < resolution_x/2 +80 && view->get_y() < resolution_y - 10 && view->get_y() > resolution_y - 38))
        hud_temp_bool[3] = 0;

    //obszar z ikoną złota
    if (view->get_x() > resolution_x/2 + 124 && view->get_x() < resolution_x/2 +200 && view->get_y() < resolution_y - 10 && view->get_y() > resolution_y - 38)
        hud_temp_bool[4] = 1;
    if (!(view->get_x() > resolution_x/2 +124  && view->get_x() < resolution_x/2 +200 && view->get_y() < resolution_y - 10 && view->get_y() > resolution_y - 38))
        hud_temp_bool[4] = 0;
}

void Game::reset_timer()
{
    start_stop();
}
