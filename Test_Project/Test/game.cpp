#include "game.h"

Game::Game(QObject *parent) : QObject(parent)
{  
    // randomize in creating all new objects
    std::srand(time(0));

    // create map
    new_game();

    // create NPCs ships
    for (int i = 0; i < start_npc_amount; i++)
    {
        create_new_npc();
        /*npc_ships.push_back(new NPC());
        scene->addItem(npc_ships[i]);
        connect(npc_ships[i], SIGNAL(delete_npc(NPC *)),
                this, SLOT(delete_npc(NPC *)));*/
    }

    // create wind to put into the scene
    //aktualnie wiatr jest na scenie nie potrzebny, zawsze można go dodać
    //scene->addItem(wind);

    //make item focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // update all NPC ships
    /*foreach (NPC * npc_ship, npc_ships)
    {
        connect (timer, SIGNAL(timeout()), npc_ship, SLOT(move_to_next_location()));
        scene->addItem(npc_ship->flag);
    }*/

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
    // kliknięcia myszki
    connect(view, SIGNAL(mouse_left_pressed()), this, SLOT(mouse_pressed()));
    // puszczenia myszki
    connect(view, SIGNAL(mouse_released()), this, SLOT(mouse_released()));
    // klawisz escape
    connect(player, SIGNAL(esc_pressed()), this, SLOT(esc_pressed()));
    // renew npc list (up to 30)
    //connect(timer, SIGNAL(timeout()), this, SLOT(create_new_npc()));

    connect(player, SIGNAL(start_battle(Ship*)), this, SLOT(start_player_battle(Ship*)));
    connect(player, SIGNAL(start_city(City*)), this, SLOT(got_to_city(City*)));
    connect(player, SIGNAL(revolt_signal()), this, SLOT(show_revolt_menu()));

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
    Wind::angle = rand() % 360;
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
    set_island(2952, 103, ":/island_a5_01.png");
    set_island(5749, 26, ":/island_a6_01.png");

    //ustawianie miast
    set_city(3444, 3108, 17, ":/town6.png", 1);
    set_city(5878, 308, 74, ":/town6.png", 2);
    set_city(5348, 3199, 37, ":/town6.png", 4);
    set_city(3140,580, 26, ":/town6.png", 4);
    set_city(5995, 1981, 65, ":/town6.png", 3);

    cities[0]->set_name(QString("Saint Kitts"));
    cities[1]->set_name(QString("San Escobar"));
    cities[2]->set_name(QString("Sint Marten"));
    cities[3]->set_name(QString("Curacao"));
    cities[4]->set_name(QString("La Desirade"));
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
    if (!player_at_battle && !player_in_city)
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

    // set hud
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
    hud_txt[2]->setPos(scene_x + resolution_x/2 - 134, hud_txt[1]->y());

    //ilość jedzenia
    hud_txt[3]->setPlainText(QString(QString::number(player->get_food())));
    hud_txt[3]->setPos(scene_x + resolution_x/2 - 53,  hud_txt[1]->y());

    //ilość stan morale
    hud_txt[4]->setPlainText(QString(QString::number(player->get_morale())));
    hud_txt[4]->setPos(scene_x + resolution_x/2 + 34,  hud_txt[1]->y());

    //ilość armat
    hud_txt[5]->setPlainText(QString(QString::number(player->get_cannons())));
    hud_txt[5]->setPos(scene_x + resolution_x - 75, scene_y + 31);

    //ilość amunicji
    hud_txt[6]->setPlainText(QString(QString::number(player->get_ammo())));
    hud_txt[6]->setPos(scene_x + resolution_x - 75, scene_y + 59);

    //ilość złota
    hud_txt[7]->setPlainText(QString(QString::number(player->get_gold())));
    hud_txt[7]->setPos(scene_x + resolution_x/2 + 121,  hud_txt[1]->y());

    //nazwa statku
    hud_txt[8]->setPlainText(QString(player->get_name()));
    hud_txt[8]->setPos(scene_x + resolution_x - 145, scene_y + 3);

    //tekst menu
    hud_txt[9]->setPos(scene_x + 45, scene_y + 10);

    //oznaczenie wersji
    hud_txt[10]->setPos(scene_x + 17, scene_y + 40);


    //stan ładowni
    for(int iterate = 0; iterate < 7; iterate++)
    {
        if(iterate == 0)
        {
            hud_cargo_img[iterate]->setPos(scene_x + resolution_x/2  - 321, scene_y);
        }
        if(iterate == 1)
        {
            hud_cargo_img[iterate]->setPos(scene_x + resolution_x/2 - 234, scene_y);
        }
        if(iterate == 2)
        {
            hud_cargo_img[iterate]->setPos(scene_x + resolution_x/2 - 146, scene_y);
        }
        if(iterate == 3)
        {
            hud_cargo_img[iterate]->setPos(scene_x + resolution_x/2 - 58, scene_y);
        }
        if(iterate == 4)
        {
            hud_cargo_img[iterate]->setPos(scene_x + resolution_x/2 + 30, scene_y);
        }
        if(iterate == 5)
        {
            hud_cargo_img[iterate]->setPos(scene_x + resolution_x/2 + 118, scene_y);
        }
        if(iterate == 6)
        {
            hud_cargo_img[iterate]->setPos(scene_x + resolution_x/2 + 206, scene_y);
        }

        if(iterate < player->get_hold_size())
        {
            hud_cargo_img[iterate]->setPixmap(QPixmap(":/" + player->get_goods()[iterate]->get_name() + "_01.png"));
            hud_cargo_txt[iterate]->setPlainText(QString(QString::number(player->get_goods()[iterate]->get_amount())));
            if(iterate == 0)
            {
                hud_cargo_txt[iterate]->setPos(scene_x + resolution_x/2  - 253, scene_y + 61);
            }
            if(iterate == 1)
            {
                hud_cargo_txt[iterate]->setPos(scene_x + resolution_x/2  - 166, hud_cargo_txt[0]->y());
            }
            if(iterate == 2)
            {
                hud_cargo_txt[iterate]->setPos(scene_x + resolution_x/2  - 78, hud_cargo_txt[0]->y());
            }
            if(iterate == 3)
            {
                hud_cargo_txt[iterate]->setPos(scene_x + resolution_x/2  + 12, hud_cargo_txt[0]->y());
            }
            if(iterate == 4)
            {
                hud_cargo_txt[iterate]->setPos(scene_x + resolution_x/2  + 100, hud_cargo_txt[0]->y());
            }
            if(iterate == 5)
            {
                hud_cargo_txt[iterate]->setPos(scene_x + resolution_x/2  + 188, hud_cargo_txt[0]->y());
            }
            if(iterate == 6)
            {
                hud_cargo_txt[iterate]->setPos(scene_x + resolution_x/2  + 276, hud_cargo_txt[0]->y());
            }
        }
        else
        {
            hud_cargo_img[iterate]->setPixmap(QPixmap(":/pedlock_03.png"));
            hud_cargo_txt[iterate]->setPos(0, 0);
        }
    }


    //elementy tymczasowe
    //stan zdrowia
    if (hud_temp_bool[0])
    {
        hud_temp_img[0]->setPos(scene_x + resolution_x/2 - 220, scene_y + resolution_y - 134);
        hud_temp_txt[0]->setPos(scene_x + resolution_x/2 - 220, scene_y + resolution_y - 136);
        hud_temp_txt[0]->setPlainText(QString("Health\n" + QString::number((int)(((float)player->get_health()/(float)player->get_max_health()) *100)) + "%\nMax\n" + QString::number(player->get_max_health())));
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
        hud_temp_txt[1]->setPos(scene_x + resolution_x/2 - 132, scene_y + resolution_y - 136);
        hud_temp_txt[1]->setPlainText(QString("Crew\n" + QString::number((int)(100*(float)player->get_crew()/(float)player->get_max_crew())) + "%\nMax\n" + QString::number(player->get_max_crew())));
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
        hud_temp_txt[2]->setPos(scene_x + resolution_x/2 - 51, scene_y + resolution_y - 136);
        hud_temp_txt[2]->setPlainText(QString("Food\n"+ QString::number((int)(100*(float)player->get_food()/(float)player->get_max_food())) + "%\nper day\n- " + QString::number(player->get_daily_food())));
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
        hud_temp_txt[3]->setPos(scene_x + resolution_x/2 + 37, scene_y + resolution_y - 136);
        switch (player->get_salary())
        {
            case 1:
                hud_temp_txt[3]->setPlainText(QString("Morale\n\nsalaries\nare very\npoor"));
                break;
            case 2:
                hud_temp_txt[3]->setPlainText(QString("Morale\n\nsalaries\narelow"));
                break;
            case 3:
                hud_temp_txt[3]->setPlainText(QString("Morale\n\nsalaries\nare fair"));
                break;
            case 4:
                hud_temp_txt[3]->setPlainText(QString("Morale\n\nsalaries\nare high"));
                break;
            case 5:
                hud_temp_txt[3]->setPlainText(QString("Morale\n\nsalaries\nare very\nhigh"));
                break;
        }
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
        hud_temp_txt[4]->setPos(scene_x + resolution_x/2 + 124, scene_y + resolution_y - 136);
    }
    else
    {
        hud_temp_img[4]->setPos(0,0);
        hud_temp_txt[4]->setPos(0,0);
    }

    //opisy
    if (hud_temp_bool[5])
    {
        hud_temp_img[5]->setPos(scene_x + view->get_x(), scene_y + view->get_y()+10);
        hud_temp_txt[5]->setPos(scene_x + view->get_x(), scene_y + view->get_y()+7);
    }
    else
    {
        hud_temp_img[5]->setPos(0,0);
        hud_temp_txt[5]->setPos(0,0);
    }

    //inne elementy HUD'u
    map_rect->setRect(
                (int)(scene_x + 8 + 285 * ((float)scene_x / (float)(8196 + 2 * border_x))),   //x
                (int)(scene_y + resolution_y - 160 - 11 + 160 * ((float)scene_y / (float)(4608 + 2* border_y))),    //y
                (int)(285 * ((float)resolution_x / (float)(8196 + 2* border_x))),   //szerokosc
                (int)(160 * ((float)resolution_y / (float)(4608 + 2* border_y)))    //wysokosc
    );

    if (battle_phase)
    {
        battle_screen_img[2]->setPixmap(QPixmap(":/" + player->get_model_name() + "_SE_01.png"));
        battle_screen_img[3]->setPixmap(QPixmap(":/" + battle_ship->get_model_name() + "_SW_01.png"));

        battle_screen_rect[0]->setRect(0, 0, (int)(150.0 * (float)player->get_health()/(float)player->get_max_health()), 14);
        if((int)(100.0 * (float)player->get_health()/(float)player->get_max_health()) >= 70)
        {
            battle_screen_rect[0]->setBrush(QBrush(QImage(":/green_02.png")));
        }
        else if((int)(100.0 * (float)player->get_health()/(float)player->get_max_health()) >= 40)
        {
            battle_screen_rect[0]->setBrush(QBrush(QImage(":/yellow_02.png")));
        }
        else
        {
            battle_screen_rect[0]->setBrush(QBrush(QImage(":/red_01.png")));
        }
        battle_screen_rect[1]->setRect(0, 0, (int)(150.0 * (float)player->get_crew()/(float)player->get_max_crew()), 14);
        if((int)(100.0 * (float)player->get_crew()/(float)player->get_max_crew()) >= 70)
        {
            battle_screen_rect[1]->setBrush(QBrush(QImage(":/green_02.png")));
        }
        else if((int)(100.0 * (float)player->get_crew()/(float)player->get_max_crew()) >= 40)
        {
            battle_screen_rect[1]->setBrush(QBrush(QImage(":/yellow_02.png")));
        }
        else
        {
            battle_screen_rect[1]->setBrush(QBrush(QImage(":/red_01.png")));
        }
        battle_screen_rect[2]->setRect(0, 0, (int)(150.0 * (float)battle_ship->get_health()/(float)battle_ship->get_max_health()), 14);
        if((int)(100.0 * (float)battle_ship->get_health()/(float)battle_ship->get_max_health()) >= 70)
        {
            battle_screen_rect[2]->setBrush(QBrush(QImage(":/green_02.png")));
        }
        else if((int)(100.0 * (float)battle_ship->get_health()/(float)battle_ship->get_max_health()) >= 40)
        {
            battle_screen_rect[2]->setBrush(QBrush(QImage(":/yellow_02.png")));
        }
        else
        {
            battle_screen_rect[2]->setBrush(QBrush(QImage(":/red_01.png")));
        }
        battle_screen_rect[3]->setRect(0, 0, (int)(150.0 * (float)battle_ship->get_crew()/(float)battle_ship->get_max_crew()), 14);
        if((int)(100.0 * (float)battle_ship->get_crew()/(float)battle_ship->get_max_crew()) >= 70)
        {
            battle_screen_rect[3]->setBrush(QBrush(QImage(":/green_02.png")));
        }
        else if((int)(100.0 * (float)battle_ship->get_crew()/(float)battle_ship->get_max_crew()) >= 40)
        {
            battle_screen_rect[3]->setBrush(QBrush(QImage(":/yellow_02.png")));
        }
        else
        {
            battle_screen_rect[3]->setBrush(QBrush(QImage(":/red_01.png")));
        }

        battle_screen_txt[3]->setPlainText(QString("health - " + QString::number(player->get_health())));
        battle_screen_txt[4]->setPlainText(QString("crew - " + QString::number(player->get_crew())));
        battle_screen_txt[5]->setPlainText(QString("Cannons: ") + QString::number(player->get_cannons()));
        battle_screen_txt[6]->setPlainText(QString("Ammo: ") + QString::number(player->get_ammo()));
        battle_screen_txt[7]->setPlainText(battle_ship->get_name());
        battle_screen_txt[8]->setPlainText(QString("health - ") + QString::number(battle_ship->get_health()));
        battle_screen_txt[9]->setPlainText(QString("crew - ") + QString::number(battle_ship->get_crew()));
        battle_screen_txt[10]->setPlainText(QString("Cannons - ") + QString::number(battle_ship->get_cannons()));
        battle_screen_txt[11]->setPlainText(QString("Ammo - ") + QString::number(battle_ship->get_ammo()));
    }
}

void Game::got_to_city(City *_city)
{
    if (!city_phase)
    {
        if (showing_npc_info)
            hide_npc_info();
        reset_timer();
        city_phase = 1;
        player->in_city = true;
        actual_city = _city;
        player_city_start_gold = player->get_gold();
        player_city_start_health = player->get_health();
        player_city_start_ammo = player->get_ammo();
        player_city_start_cannons = player->get_cannons();
        player_city_start_crew = player->get_crew();
        player_city_start_salary = player->get_salary();
        player_city_start_goods = player->get_goods();
        show_city_menu(city_phase);
    }
}

void Game::leave_city()
{
    hide_city_menu(city_phase);
    city_phase = 0;
    player_in_city = false;
    player->in_city = false;
    player->reset_day();
    reset_timer();
}

void Game::start_player_battle(Ship *_ship)
{
    if (!battle_phase)
    {
        if (showing_npc_info)
            hide_npc_info();
        reset_timer();
        battle_phase = 1;
        battle_ship = _ship;
        battle(battle_phase);
    }
}

void Game::end_player_battle(short _status)
{
    if (!_status)
    {
        hide_battle_menu(battle_phase);
        battle_phase = 0;
        player->in_battle = false;
        player_at_battle = false;
        reset_timer();
    } else
    {
        switch(_status)
        {
            case 1:
                end_battle_menu_text->setPlainText(QString("You lost and ran away on a boat."));
                break;
            case 2:
                end_battle_menu_text->setPlainText(QString("You lost but fortunately ran away."));
                break;
            case 3:
                end_battle_menu_text->setPlainText(QString("You won and sank the opponent's ship!"));
                break;
            case 4:
                end_battle_menu_text->setPlainText(QString("You won and let the opponent's ship go!"));
                break;
        }
        hide_battle_menu(battle_phase);
        battle_phase = 11;
        show_battle_menu(battle_phase);
    }
    //reset_timer();
    //create_new_npc();
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
    hud_img[iterate]->setPixmap(QPixmap(":/Interface_LD_03.png"));
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


    // parametry npc
    npc_info_bar->setPixmap(QPixmap(":/temp__npc_info_02.png"));

    info_name_text->setFont(QFont("times", 12));
    info_model_text->setFont(QFont("times", 12));
    info_health_text->setFont(QFont("times", 12));
    info_crew_text->setFont(QFont("times", 12));

    //paski parametrów
    //pasek zdrowia
    npc_status_bars.push_back(new QGraphicsRectItem(0,0,100,12));
    npc_status_bars[0]->setBrush(QBrush(QImage(":/red_01.png")));
    npc_status_bars[0]->setOpacity(0.75);
    //map_rect->setOpacity(0.5);
    npc_status_bars.push_back(new QGraphicsRectItem(0,0,100,12));
    //pasek zalogi
    npc_status_bars.push_back(new QGraphicsRectItem(0,0,100,12));
    npc_status_bars[2]->setBrush(QBrush(QImage(":/red_01.png")));
    npc_status_bars[2]->setOpacity(0.75);
    npc_status_bars.push_back(new QGraphicsRectItem(0,0,100,12));


    // elementy menu początku walki
    iterate = 0;
    // głowne menu wspływające [0]
    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/Message_bar_02.png"));
    iterate++;

    // przycisk dla tak [1]
    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/Small_button_01.png"));
    iterate++;

    // przycisk dla nie [2]
    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/Small_button_01.png"));
    iterate++;

    // ptaszek na tak [3]
    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/tick_off_01.png"));
    iterate++;

    // krzyżyk na nie [4]
    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/cross_off_01.png"));
    iterate++;

    // przycisk dla menu potwierdzenia [5]
    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/big_button_01.png"));
    iterate++;

    // ptaszek na menu potwierdzenia [6]
    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/tick_off_01.png"));
    iterate++;

    battle_start_menu_text->setPlainText(QString("Would you like to start a battle?"));
    battle_start_menu_text->setDefaultTextColor(Qt::white);
    battle_start_menu_text->setFont(QFont("times", 12));

    city_start_menu_text->setPlainText(QString("Would you like to land in the city?"));
    city_start_menu_text->setDefaultTextColor(Qt::white);
    city_start_menu_text->setFont(QFont("times", 12));

    leave_city_text->setPlainText(QString("Would you like to leave the city?"));
    leave_city_text->setDefaultTextColor(Qt::white);
    leave_city_text->setFont(QFont("times", 12));

    revolt_text->setPlainText(QString("Revolt on the ship. Ran away on a boat."));
    revolt_text->setDefaultTextColor(Qt::white);
    revolt_text->setFont(QFont("times", 12));

    end_battle_menu_text->setDefaultTextColor(Qt::white);
    end_battle_menu_text->setFont(QFont("times", 12));


    //elementy walki morskiej
    //czesc graficzna
    iterate = 0;

    // główne menu walki [0]
    battle_screen_img.push_back(new QGraphicsPixmapItem());
    battle_screen_img[iterate]->setPixmap(QPixmap(":/battle_screen_02.png"));
    iterate++;

    // przycisk uciec [1]
    battle_screen_img.push_back(new QGraphicsPixmapItem());
    battle_screen_img[iterate]->setPixmap(QPixmap(":/medium_button_01.png"));
    iterate++;

    // statek gracza [2]
    battle_screen_img.push_back(new QGraphicsPixmapItem());
    iterate++;

    // statek przeciwnika [3]
    battle_screen_img.push_back(new QGraphicsPixmapItem());
    iterate++;

    //czesc tekstowa
    iterate = 0;

    //tutul [0]
    battle_screen_txt.push_back(new QGraphicsTextItem());
    battle_screen_txt[iterate]->setPlainText(QString("Sea battle"));
    battle_screen_txt[iterate]->setDefaultTextColor(Qt::white);
    battle_screen_txt[iterate]->setFont(QFont("times", 22));
    iterate++;

    //napis guzika [1]
    battle_screen_txt.push_back(new QGraphicsTextItem());
    battle_screen_txt[iterate]->setPlainText(QString("Run away!"));
    battle_screen_txt[iterate]->setDefaultTextColor(Qt::white);
    battle_screen_txt[iterate]->setFont(QFont("times", 16));
    iterate++;

    //you [2]
    battle_screen_txt.push_back(new QGraphicsTextItem());
    battle_screen_txt[iterate]->setPlainText(QString("You"));
    battle_screen_txt[iterate]->setFont(QFont("times", 14));
    iterate++;

    //twoje zdrowie [3]
    battle_screen_txt.push_back(new QGraphicsTextItem());
    battle_screen_txt[iterate]->setPlainText(QString("health - " + QString::number(player->get_health())));
    battle_screen_txt[iterate]->setFont(QFont("times", 14));
    iterate++;

    //twoja zaloga [4]
    battle_screen_txt.push_back(new QGraphicsTextItem());
    battle_screen_txt[iterate]->setPlainText(QString("crew - " + QString::number(player->get_crew())));
    battle_screen_txt[iterate]->setFont(QFont("times", 14));
    iterate++;

    //twoj model
    //battle_screen_txt.push_back(new QGraphicsTextItem());
    //battle_screen_txt[iterate]->setPlainText(player->get_model_name());
    //battle_screen_txt[iterate]->setFont(QFont("times", 12));
    //iterate++;

    //twoje armaty [5]
    battle_screen_txt.push_back(new QGraphicsTextItem());
    battle_screen_txt[iterate]->setPlainText(QString("Cannons: ") + QString::number(player->get_cannons()));
    battle_screen_txt[iterate]->setFont(QFont("times", 14));
    iterate++;

    //twoja amunicja [6]
    battle_screen_txt.push_back(new QGraphicsTextItem());
    battle_screen_txt[iterate]->setPlainText(QString("Ammo: ") + QString::number(player->get_ammo()));
    battle_screen_txt[iterate]->setFont(QFont("times", 14));
    iterate++;

    //wrog [7]
    battle_screen_txt.push_back(new QGraphicsTextItem());
    //battle_screen_txt[iterate]->setPlainText(battle_ship->get_name());
    battle_screen_txt[iterate]->setFont(QFont("times", 14));
    iterate++;

    //zdrowie wroga [8]
    battle_screen_txt.push_back(new QGraphicsTextItem());
    //battle_screen_txt[iterate]->setPlainText(QString("health - ") + QString::number(battle_ship->get_health()));
    battle_screen_txt[iterate]->setFont(QFont("times", 14));
    iterate++;

    //zaloga wroga [9]
    battle_screen_txt.push_back(new QGraphicsTextItem());
    //battle_screen_txt[iterate]->setPlainText(QString("crew - ") + QString::number(battle_ship->get_crew()));
    battle_screen_txt[iterate]->setFont(QFont("times", 14));
    iterate++;

    //armaty wroga [10]
    battle_screen_txt.push_back(new QGraphicsTextItem());
    //battle_screen_txt[iterate]->setPlainText(QString("Cannons - ") + QString::number(battle_ship->get_cannons()));
    battle_screen_txt[iterate]->setFont(QFont("times", 14));
    iterate++;

    //ammo wroga [11]
    battle_screen_txt.push_back(new QGraphicsTextItem());
    //battle_screen_txt[iterate]->setPlainText(QString("Ammo - ") + QString::number(battle_ship->get_ammo()));
    battle_screen_txt[iterate]->setFont(QFont("times", 14));
    iterate++;

    //obiekty paskow
    iterate = 0;
    battle_screen_rect.push_back(new QGraphicsRectItem(0,0,10,10));
    battle_screen_rect[iterate]->setBrush(QBrush(QImage(":/red_01.png")));
    iterate++;
    battle_screen_rect.push_back(new QGraphicsRectItem(0,0,10,10));
    battle_screen_rect[iterate]->setBrush(QBrush(QImage(":/red_01.png")));
    iterate++;
    battle_screen_rect.push_back(new QGraphicsRectItem(0,0,10,10));
    battle_screen_rect[iterate]->setBrush(QBrush(QImage(":/red_01.png")));
    iterate++;
    battle_screen_rect.push_back(new QGraphicsRectItem(0,0,10,10));
    battle_screen_rect[iterate]->setBrush(QBrush(QImage(":/red_01.png")));
    iterate++;

    //elementy fazy abordażu
    sink_abordage_menu_text->setPlainText(QString("Would you like to start abordage?"));
    sink_abordage_menu_text->setDefaultTextColor(Qt::white);
    sink_abordage_menu_text->setFont(QFont("times", 12));

    sink_let_go_menu_text->setPlainText(QString("Would you like to let the ship go?"));
    sink_let_go_menu_text->setDefaultTextColor(Qt::white);
    sink_let_go_menu_text->setFont(QFont("times", 12));

    menu_bar->setPixmap(QPixmap(":/Menu_bar_03.png"));
    for (iterate = 0; iterate < 5; iterate++)
    {
        menu_buttons.push_back(new QGraphicsPixmapItem());
        menu_buttons[iterate]->setPixmap(QPixmap(":/big_button_02.png"));
    }

    // elementy miasta
    // stocznia img
    iterate = 0;

    // main menu [0]
    shipyard_img.push_back(new QGraphicsPixmapItem);
    shipyard_img[iterate]->setPixmap(QPixmap(":/shipyard_screen_02.png"));
    iterate++;

    // button back [1]
    shipyard_img.push_back(new QGraphicsPixmapItem);
    shipyard_img[iterate]->setPixmap(QPixmap(":/medium_button_01.png"));
    iterate++;

    // button accept [2]
    shipyard_img.push_back(new QGraphicsPixmapItem);
    shipyard_img[iterate]->setPixmap(QPixmap(":/medium_button_01.png"));
    iterate++;

    // plus for ship1 [3]
    shipyard_img.push_back(new QGraphicsPixmapItem);
    shipyard_img[iterate]->setPixmap(QPixmap(":/plus_off_02.png"));
    iterate++;

    // plus for ship2 [4]
    shipyard_img.push_back(new QGraphicsPixmapItem);
    shipyard_img[iterate]->setPixmap(QPixmap(":/plus_off_02.png"));
    iterate++;

    // plus for health [5]
    shipyard_img.push_back(new QGraphicsPixmapItem);
    shipyard_img[iterate]->setPixmap(QPixmap(":/plus_off_02.png"));
    iterate++;

    // plus for cannons [6]
    shipyard_img.push_back(new QGraphicsPixmapItem);
    shipyard_img[iterate]->setPixmap(QPixmap(":/plus_off_02.png"));
    iterate++;

    // plus for ammo [7]
    shipyard_img.push_back(new QGraphicsPixmapItem);
    shipyard_img[iterate]->setPixmap(QPixmap(":/plus_off_02.png"));
    iterate++;

    // minus for health [8]
    shipyard_img.push_back(new QGraphicsPixmapItem);
    shipyard_img[iterate]->setPixmap(QPixmap(":/minus_off_02.png"));
    iterate++;

    // minus for cannons [9]
    shipyard_img.push_back(new QGraphicsPixmapItem);
    shipyard_img[iterate]->setPixmap(QPixmap(":/minus_off_02.png"));
    iterate++;

    // minus for ammo [10]
    shipyard_img.push_back(new QGraphicsPixmapItem);
    shipyard_img[iterate]->setPixmap(QPixmap(":/minus_off_02.png"));
    iterate++;

    // ship1 [11]
    shipyard_img.push_back(new QGraphicsPixmapItem);
    iterate++;

    // ship2 [12]
    shipyard_img.push_back(new QGraphicsPixmapItem);
    iterate++;

    // stocznia txt
    // tekst nad zdrowiem [0], tekst nad armatami [1], tekst nad amunicją [2]
    for (iterate = 0; iterate < 3; iterate++)
    {
        shipyard_txt.push_back(new QGraphicsTextItem());
        shipyard_txt[iterate]->setFont(QFont("times", 12));
        shipyard_txt[iterate]->setDefaultTextColor(Qt::black);
    }

    // tekst zdrowia [3], tekst armat [4], tekst amunicji [5]
    for (iterate = 3; iterate < 6; iterate++)
    {
        shipyard_txt.push_back(new QGraphicsTextItem());
        shipyard_txt[iterate]->setFont(QFont("times", 14));
        shipyard_txt[iterate]->setDefaultTextColor(Qt::black);
    }

    //tytuly statkow
    for(iterate = 6; iterate < 8; iterate++)
    {
        shipyard_txt.push_back(new QGraphicsTextItem());
        shipyard_txt[iterate]->setFont(QFont("times", 14));
        shipyard_txt[iterate]->setDefaultTextColor(Qt::black);
    }

    //ceny statkow
    for (iterate = 8; iterate < 10; iterate++)
    {
        shipyard_txt.push_back(new QGraphicsTextItem());
        shipyard_txt[iterate]->setFont(QFont("times", 14));
        shipyard_txt[iterate]->setDefaultTextColor(Qt::black);
    }

    //opis statkow
    for (iterate = 10; iterate < 12; iterate++)
    {
        shipyard_txt.push_back(new QGraphicsTextItem());
        shipyard_txt[iterate]->setFont(QFont("times", 12));
        shipyard_txt[iterate]->setDefaultTextColor(Qt::black);
    }


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

    //nazwa statku
    hud_txt.push_back(new QGraphicsTextItem());
    hud_txt[iterate]->setPlainText(QString(player->get_model_name()));
    hud_txt[iterate]->setFont(QFont("times", 13));
    scene->addItem(hud_txt[iterate]);
    iterate++;

    //tekst menu
    hud_txt.push_back(new QGraphicsTextItem());
    hud_txt[iterate]->setPlainText(QString("MENU"));
    hud_txt[iterate]->setFont(QFont("times", 16));
    //qDebug() << hud_txt[iterate]->size();
    scene->addItem(hud_txt[iterate]);
    iterate++;

    //tekst wersji
    hud_txt.push_back(new QGraphicsTextItem());
    hud_txt[iterate]->setPlainText(QString("Version ") + QString("Pre Alpha ") + QString::number(version));
    hud_txt[iterate]->setFont(QFont("times", 8));
    hud_txt[iterate]->setDefaultTextColor(Qt::lightGray);
    hud_txt[iterate]->setOpacity(0.5);
    //qDebug() << hud_txt[iterate]->size();
    scene->addItem(hud_txt[iterate]);

    //wypełnianie ładowni
    for(int i = 0; i < 7; i++)
    {
        if(i < player->get_hold_size())
        {
            hud_cargo_img.push_back(new QGraphicsPixmapItem());
            hud_cargo_img[i]->setPixmap(QPixmap(":/" + player->get_goods()[i]->get_name() + "_01.png"));
            scene->addItem(hud_cargo_img[i]);
            hud_cargo_txt.push_back(new QGraphicsTextItem());
            hud_cargo_txt[i]->setPlainText(QString(QString::number(player->get_goods()[i]->get_amount())));
            hud_cargo_txt[i]->setFont(QFont("times", 11));
            scene->addItem(hud_cargo_txt[i]);
        }
        else
        {
            hud_cargo_img.push_back(new QGraphicsPixmapItem());
            hud_cargo_img[i]->setPixmap(QPixmap(":/pedlock_03.png"));
            scene->addItem(hud_cargo_img[i]);
            hud_cargo_txt.push_back(new QGraphicsTextItem());
            hud_cargo_txt[i]->setPlainText(QString("wartosc"));
            hud_cargo_txt[i]->setFont(QFont("times", 11));
            scene->addItem(hud_cargo_txt[i]);
        }
    }


    //elementy graficzne tymczasowe, odpowiadające im elementy tekstowe i bool'owskie
    iterate = 0;

    //stan zdrowia
    hud_temp_img.push_back(new QGraphicsPixmapItem());
    hud_temp_img[iterate]->setPixmap(QPixmap(":/temp_health_01.png"));
    scene->addItem(hud_temp_img[iterate]);
    //hud_temp_img[iterate]->setPos(0,0);

    hud_temp_txt.push_back(new QGraphicsTextItem());
    hud_temp_txt[iterate]->setPlainText(QString("Health\n" + QString::number((int)(((float)player->get_health()/(float)player->get_max_health()) *100)) + "%\nMax\n" + QString::number(player->get_max_health())));
    hud_temp_txt[iterate]->setFont(QFont("times", 12));
    scene->addItem(hud_temp_txt[iterate]);
    //hud_temp_txt[iterate]->setPos(0,0);

    hud_temp_bool.push_back(0);
    iterate++;

    //stan załogi
    hud_temp_img.push_back(new QGraphicsPixmapItem());
    hud_temp_img[iterate]->setPixmap(QPixmap(":/temp_crew_01.png"));
    scene->addItem(hud_temp_img[iterate]);
    //hud_temp_img[iterate]->setPos(0,0);

    hud_temp_txt.push_back(new QGraphicsTextItem());
    hud_temp_txt[iterate]->setPlainText(QString("Crew\n" + QString::number((int)(100*(float)player->get_crew()/(float)player->get_max_crew())) + "%\nMax\n" + QString::number(player->get_max_crew())));
    hud_temp_txt[iterate]->setFont(QFont("times", 12));
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
    hud_temp_txt[iterate]->setPlainText(QString("Food\n"+ QString::number((int)(100*(float)player->get_food()/(float)player->get_max_food())) + "%\nper day\n- " + QString::number(player->get_daily_food())));
    hud_temp_txt[iterate]->setFont(QFont("times", 12));
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
    hud_temp_txt[iterate]->setFont(QFont("times", 12));
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
    hud_temp_txt[iterate]->setPlainText(QString("Gold\n- " + QString::number(player->get_daily_salary()) + "\nper day"));
    hud_temp_txt[iterate]->setFont(QFont("times", 13));
    scene->addItem(hud_temp_txt[iterate]);
    //hud_temp_txt[iterate]->setPos(0,0);

    hud_temp_bool.push_back(0);
    iterate++;

    //opis
    hud_temp_img.push_back(new QGraphicsPixmapItem());
    hud_temp_img[iterate]->setPixmap(QPixmap(":/temp_bg_01.png"));
    scene->addItem(hud_temp_img[iterate]);
    hud_temp_img[iterate]->setPos(0,0);

    hud_temp_txt.push_back(new QGraphicsTextItem());
    hud_temp_txt[iterate]->setPlainText(QString("Description"));
    hud_temp_txt[iterate]->setFont(QFont("times", 12));
    scene->addItem(hud_temp_txt[iterate]);
    hud_temp_txt[iterate]->setPos(0,0);

    hud_temp_bool.push_back(0);
    iterate++;


    //Prostokącik na mapie
    map_rect = new QGraphicsRectItem();
    //map_rect->setRect(scene_x + 15 + 265 * ((float)scene_x / (8196 + 2 * border_x)), scene_y + resolution_y - 156 + 148 * ((float)scene_y / (4608 + 2* border_y)), (int)(267 * ((float)resolution_x / (8196 + 2* border_x))), (int)(151 * ((float)resolution_y / (4608 + 2* border_y))));
    scene->addItem(map_rect);

    //ważne poniżej
    //map_rect->setOpacity(0.1);
    //map_rect->setBrush(QBrush(QImage(":/img/Sea/sea_01.png")));

    //tworzenie menu
    iterate = 0;

    //tekst głównego menu
    for(int i = 0; i < 6; i++)
    {
        menu_text.push_back(new QGraphicsTextItem());
        menu_text[i]->setFont(QFont("times", 16));
        menu_text[i]->setDefaultTextColor(Qt::white);
    }

    menu_text[0]->setPlainText(QString("Save game"));
    menu_text[0]->setDefaultTextColor(Qt::darkGray);

    menu_text[1]->setPlainText(QString("Load game"));
    menu_text[1]->setDefaultTextColor(Qt::darkGray);

    menu_text[2]->setPlainText(QString("Options"));

    menu_text[3]->setPlainText(QString("Exit game"));

    menu_text[4]->setPlainText(QString("Continue"));

    menu_text[5]->setPlainText(QString("Main menu"));
    menu_text[5]->setDefaultTextColor(Qt::darkGray);
    menu_text[5]->setFont(QFont("times", 12));

    //tekst menu miasta
    for(int i = 0; i < 7; i++)
    {
        city_menu_text.push_back(new QGraphicsTextItem());
        city_menu_text[i]->setFont(QFont("times", 16));
        city_menu_text[i]->setDefaultTextColor(Qt::darkGray);
    }

    city_menu_text[0]->setPlainText(QString("Governor"));
    //city_menu_text[0]->setDefaultTextColor(Qt::darkGray);

    city_menu_text[1]->setPlainText(QString("Tradesman"));
    city_menu_text[1]->setDefaultTextColor(Qt::white);
    //city_menu_text[1]->setDefaultTextColor(Qt::darkGray);

    city_menu_text[2]->setPlainText(QString("Tavern"));
    city_menu_text[2]->setDefaultTextColor(Qt::white);

    city_menu_text[3]->setPlainText(QString("Shipyard"));
    city_menu_text[3]->setDefaultTextColor(Qt::white);

    city_menu_text[4]->setPlainText(QString("Leave city"));
    city_menu_text[4]->setDefaultTextColor(Qt::white);

    city_menu_text[5]->setPlainText(QString("City menu"));
    city_menu_text[5]->setDefaultTextColor(Qt::darkGray);
    city_menu_text[5]->setFont(QFont("times", 12));

    city_menu_text[6]->setPlainText(QString("Back"));
    city_menu_text[6]->setDefaultTextColor(Qt::white);
}

void Game::set_island(short _x, short _y, QString _pixmap_name)
{
    islands.push_back(new Island());
    islands[islands.size() - 1]->setPixmap(QPixmap(_pixmap_name));
    scene->addItem(islands[islands.size() - 1]);
    islands[islands.size() - 1]->setPos(_x, _y);
}

void Game::set_city(short _x, short _y, short _voronoi_id, QString _pixmap_name, short _fraction)
{
    cities.push_back(new City(_voronoi_id, _fraction, cities.size() + 1));
    cities[cities.size() - 1]->setPixmap(QPixmap(_pixmap_name));
    scene->addItem(cities[cities.size() - 1]);
    cities[cities.size() - 1]->setPos(_x, _y);
}

void Game::start_stop()
{
    if (pause)
        timer->start(frame_time);
    else
        timer->stop();
    pause = !pause;
}

void Game::show_menu()
{
    if (!battle_phase && !city_phase)
        reset_timer();
    if (!menu_bool)
    {
        scene->addItem(menu_bar);
        menu_bar->setPos(scene_x + resolution_x/2 - menu_bar->pixmap().width()/2, scene_y + resolution_y/2 - menu_bar->pixmap().height()/2);

        for (short i = 0; i < 5; i++)
        {
            scene->addItem(menu_buttons[i]);
            if (i == 4)
                menu_buttons[i]->setPos(menu_bar->x() + menu_bar->pixmap().width()/2 - menu_buttons[i]->pixmap().width()/2,
                                        menu_bar->y() + 400);
            else
                menu_buttons[i]->setPos(menu_bar->x() + menu_bar->pixmap().width()/2 - menu_buttons[i]->pixmap().width()/2,
                                        menu_bar->y() + 113 + i*63);
            scene->addItem(menu_text[i]);
            menu_text[i]->setPos(menu_buttons[i]->x() + menu_buttons[i]->pixmap().width()/2 - menu_text[i]->boundingRect().width()/2,
                                 menu_buttons[i]->y() + 6);
        }

        scene->addItem(menu_text[5]);
        menu_text[5]->setPos(menu_bar->x() + menu_bar->pixmap().width()/2 - menu_text[5]->boundingRect().width()/2, menu_bar->y() + 45);
    }
    else
    {
        scene->removeItem(menu_bar);
        for(int i = 0; i < 6; i++)
            scene->removeItem(menu_text[i]);
        for(int i = 0; i < 5; i++)
            scene->removeItem(menu_buttons[i]);
    }
    menu_bool = !menu_bool;
}

void Game::battle(short _battle_phase)
{
    switch(_battle_phase)
    {
        case 1:
            show_battle_menu(1);
            player->in_battle = true;
            break;
        case 2:
            if (!player_at_battle)
            {
                player_at_battle = true;
                player->lower_the_sails();
                battles.push_back(new Battle(player, battle_ship));
                connect(battles[battles.size()-1], SIGNAL(finish_battle(short)), this, SLOT(end_player_battle(short)));
                connect(battles[battles.size()-1], SIGNAL(finish_battle(short)), battle_ship, SLOT(reset()));
                connect(battles[battles.size()-1], SIGNAL(update_info()), this, SLOT(center_view()));
                connect(battles[battles.size()-1], SIGNAL(lost(short)), player, SLOT(on_boat(short)));
                connect(battles[battles.size()-1], SIGNAL(sink_abordage(short)), this, SLOT(show_battle_menu(short)));
                connect(this, SIGNAL(sink_abordage(short)), battles[battles.size()-1], SLOT(after_sea_battle(short)));
                connect(battles[battles.size()-1], SIGNAL(sink_let_go(short)), this, SLOT(show_battle_menu(short)));
                connect(this, SIGNAL(sink_let_go(bool)), battles[battles.size()-1], SLOT(win_abordage(bool)));
                connect(this, SIGNAL(run_away()), battles[battles.size()-1], SLOT(run_away()));
            }
            break;
    }
}

void Game::show_city_menu(short _city_phase)
{
    /*
    0 - poza miastem
    1 - czy chcę grać wejść do miasta
    2 - główne menu
    3 - gubernator
    4 - stocznia
    5 - tawerna
    6 - sklep
    7 - czy chcę grać wyjść z miasta
    */
    //short iter;
    switch(_city_phase)
    {
        case 1:
            show_first_menu();
            break;
        case 2:
            scene->addItem(menu_bar);
            menu_bar->setPos(scene_x + resolution_x/2 - menu_bar->pixmap().width()/2,
                             scene_y + resolution_y/2 - menu_bar->pixmap().height()/2);

            for (short i = 0; i < 5; i++)
            {
                scene->addItem(menu_buttons[i]);
                if (i == 4)
                    menu_buttons[i]->setPos(menu_bar->x() + menu_bar->pixmap().width()/2 - menu_buttons[i]->pixmap().width()/2,
                                            menu_bar->y() + 400);
                else
                    menu_buttons[i]->setPos(menu_bar->x() + menu_bar->pixmap().width()/2 - menu_buttons[i]->pixmap().width()/2,
                                            menu_bar->y() + 113 + i*63);
                scene->addItem(city_menu_text[i]);
                city_menu_text[i]->setPos(menu_buttons[i]->x() + menu_buttons[i]->pixmap().width()/2 - city_menu_text[i]->boundingRect().width()/2,
                                     menu_buttons[i]->y() + 6);
            }

            city_menu_text[5]->setPlainText(actual_city->get_name());
            scene->addItem(city_menu_text[5]);
            city_menu_text[5]->setPos(menu_bar->x() + menu_bar->pixmap().width()/2 - city_menu_text[5]->boundingRect().width()/2, menu_bar->y() + 45);
            break;
        case 4:
            scene->addItem(shipyard_img[0]);
            shipyard_img[0]->setPos(scene_x + resolution_x/2 - shipyard_img[0]->pixmap().width()/2,
                             scene_y + resolution_y/2 - shipyard_img[0]->pixmap().height()/2);
            scene->addItem(shipyard_img[1]);
            shipyard_img[1]->setPos(shipyard_img[0]->x() + 450, shipyard_img[0]->y() + 275);
            scene->addItem(city_menu_text[6]);
            city_menu_text[6]->setPos(shipyard_img[1]->x() + shipyard_img[1]->pixmap().width()/2
                                                           - city_menu_text[6]->boundingRect().width()/2,
                                      shipyard_img[1]->y() + 7);
            // elementy img
            for (short i = 3; i < 13; i++)
                scene->addItem(shipyard_img[i]);
            shipyard_img[3]->setPos(shipyard_img[0]->x() + 284, shipyard_img[0]->y() + 169);
            shipyard_img[4]->setPos(shipyard_img[3]->x(), shipyard_img[3]->y() + 126);
            shipyard_img[5]->setPos(shipyard_img[0]->x() + 516, shipyard_img[0]->y() + 51);
            shipyard_img[6]->setPos(shipyard_img[5]->x(), shipyard_img[5]->y() + 80);
            shipyard_img[7]->setPos(shipyard_img[6]->x(), shipyard_img[6]->y() + 87);
            shipyard_img[8]->setPos(shipyard_img[5]->x() - 83, shipyard_img[5]->y());
            shipyard_img[9]->setPos(shipyard_img[8]->x(), shipyard_img[6]->y());
            shipyard_img[10]->setPos(shipyard_img[8]->x(), shipyard_img[7]->y());

            shipyard_img[11]->setPixmap(QPixmap(actual_city->get_selling_ship_img(0)));
            shipyard_img[12]->setPixmap(QPixmap(actual_city->get_selling_ship_img(1)));
            shipyard_img[11]->setPos(shipyard_img[0]->x() + 55, shipyard_img[0]->y()+100);
            shipyard_img[12]->setPos(shipyard_img[0]->x() + 55, shipyard_img[0]->y()+225);

            // elementy txt
            shipyard_txt[0]->setPlainText(QString("Repair your ship \n100 " + currency + "/unit"));
            shipyard_txt[1]->setPlainText(QString("Buy/sell cannons \n35 " + currency + "/item"));
            shipyard_txt[2]->setPlainText(QString(" Buy/sell ammo \n10 " + currency + "/item"));
            for (short i = 0; i < 3; i++)
            {
                scene->addItem(shipyard_txt[i]);
                shipyard_txt[i]->setPos(shipyard_img[i+8]->x() + 54 - shipyard_txt[i]->boundingRect().width()/2,
                                        shipyard_img[i+8]->y() - 42);
            }

            shipyard_txt[3]->setPlainText(QString::number(short(100 * double(player->get_health()) /
                                                                             player->get_max_health())) + QString("%"));
            shipyard_txt[4]->setPlainText(QString::number(player->get_cannons()));
            shipyard_txt[5]->setPlainText(QString::number(player->get_ammo()));
            for (short i = 3; i < 6; i++)
            {
                scene->addItem(shipyard_txt[i]);
                shipyard_txt[i]->setPos(shipyard_img[i+5]->x() + 55 - shipyard_txt[i]->boundingRect().width()/2,
                                        shipyard_img[i+5]->y()-5);
            }

            shipyard_txt[6]->setPlainText(actual_city->get_selling_ship_name(0));
            //scene->addItem(shipyard_txt[6]);
            shipyard_txt[6]->setPos(shipyard_img[0]->x()+150, shipyard_img[0]->y()+80);
            shipyard_txt[7]->setPlainText(actual_city->get_selling_ship_name(1));
            //scene->addItem(shipyard_txt[7]);
            shipyard_txt[7]->setPos(shipyard_img[0]->x()+150, shipyard_img[0]->y()+208);

            shipyard_txt[8]->setPlainText(QString::number(actual_city->get_selling_ship_price(0)) + QString(" ") + currency);
            shipyard_txt[8]->setPos(shipyard_img[0]->x()+150, shipyard_img[0]->y()+99);
            shipyard_txt[9]->setPlainText(QString::number(actual_city->get_selling_ship_price(1)) + QString(" ") + currency);
            shipyard_txt[9]->setPos(shipyard_img[0]->x()+150, shipyard_img[0]->y()+227);

            shipyard_txt[10]->setPlainText(actual_city->get_selling_ship_description(0));
            shipyard_txt[10]->setPos(shipyard_img[0]->x()+150, shipyard_img[0]->y()+121);
            shipyard_txt[11]->setPlainText(actual_city->get_selling_ship_description(1));
            shipyard_txt[11]->setPos(shipyard_img[0]->x()+150, shipyard_img[0]->y()+249);

            for(int i = 6; i < 12; i++)
            {
                scene->addItem(shipyard_txt[i]);
            }

            break;
        case 7:
            show_first_menu();
    }
}

void Game::hide_city_menu(short _city_phase)
{
    switch(_city_phase)
    {
        case 1:
            hide_first_menu();
            break;
        case 2:
            scene->removeItem(menu_bar);
            for(short i = 0; i < 6; i++)
                scene->removeItem(city_menu_text[i]);
            for(short i = 0; i < 5; i++)
                scene->removeItem(menu_buttons[i]);
            break;
        case 4:
            for (size_t i = 0; i < shipyard_img.size(); i++)
                scene->removeItem(shipyard_img[i]);
            for (size_t i = 0; i < shipyard_txt.size(); i++)
                scene->removeItem(shipyard_txt[i]);
            scene->removeItem(city_menu_text[6]);
        case 7:
            hide_first_menu();
            break;
    }
}


void Game::show_battle_menu(short _battle_phase)
{
    /*
    0 - no battle
    1 - question if start battle
    2 - sea battle
    3 - question if start abordage
    4 - abordage
    5 - question if let the ship go
    6 - sink (kill) the ship
    7 - let the ship go
    8 - run away from sea battle
    9 - loose either in sea battle or abordage
    10 - show and change ship holds / get crew from NPC (?)
    11 - end battle message
    */
    short iter;
    switch(_battle_phase)
    {
        case 1:
            show_first_menu();
            break;
        case 2:
            battle_screen_txt[0]->setPlainText(QString("Sea battle"));
        case 4:
            if(battle_phase == 4)
            {
                battle_screen_txt[0]->setPlainText(QString("Abordage"));
            }
            hide_battle_menu(1);
            center_view();
            //to do
            //elementy graficzne
            iter =  0;
            scene->addItem(battle_screen_img[iter]);
            battle_screen_img[iter]->setPos(scene_x + resolution_x/2 - battle_screen_img[iter]->pixmap().width()/2,scene_y + resolution_y/2 - battle_screen_img[iter]->pixmap().height()/2);
            iter++;

            scene->addItem(battle_screen_img[iter]);
            battle_screen_img[iter]->setPos(scene_x + resolution_x/2 - battle_screen_img[iter]->pixmap().width()/2,scene_y + resolution_y/2 - battle_screen_img[iter]->pixmap().height()/2 + 100);
            iter++;

            scene->addItem(battle_screen_img[iter]);
            battle_screen_img[iter]->setPos(battle_screen_img[0]->x() + 70, battle_screen_img[0]->y() + 54);
            iter++;

            scene->addItem(battle_screen_img[iter]);
            battle_screen_img[iter]->setPos(battle_screen_img[0]->x() + 445, battle_screen_img[2]->y());

            //elementy tekstowe
            iter = 0;

            //tytul
            scene->addItem(battle_screen_txt[iter]);
            battle_screen_txt[iter]->setPos(battle_screen_img[0]->x() + battle_screen_img[0]->pixmap().width()/2
                                                                      - battle_screen_txt[iter]->boundingRect().width()/2,
                                            battle_screen_img[0]->y() + 25);
            iter++;

            //przycisk guzika "Run!"
            scene->addItem(battle_screen_txt[iter]);
            battle_screen_txt[iter]->setPos(battle_screen_img[0]->x() + battle_screen_img[0]->pixmap().width()/2
                                                                      - battle_screen_txt[iter]->boundingRect().width()/2,
                                            battle_screen_img[1]->y() + 8);
            iter++;

            //nazwa player
            scene->addItem(battle_screen_txt[iter]);
            battle_screen_txt[iter]->setPos(battle_screen_img[0]->x() + 40, battle_screen_img[0]->y() + 147);
            iter++;

            //stan zdrowia
            scene->addItem(battle_screen_txt[iter]);
            battle_screen_txt[iter]->setPos(battle_screen_txt[2]->x(), battle_screen_img[0]->y() + 173);
            iter++;

            //stan zalogi
            scene->addItem(battle_screen_txt[iter]);
            battle_screen_txt[iter]->setPos(battle_screen_txt[2]->x(), battle_screen_img[0]->y() + 213);
            iter++;

            //armaty
            scene->addItem(battle_screen_txt[iter]);
            battle_screen_txt[iter]->setPos(battle_screen_txt[2]->x(), battle_screen_img[0]->y() + 255);
            iter++;

            //ammo
            scene->addItem(battle_screen_txt[iter]);
            battle_screen_txt[iter]->setPos(battle_screen_txt[2]->x(), battle_screen_img[0]->y() + 280);
            iter++;

            //nazwa wroga
            scene->addItem(battle_screen_txt[iter]);
            battle_screen_txt[iter]->setPos(battle_screen_img[0]->x() + 410, battle_screen_txt[2]->y());
            iter++;

            //stan zdrowia
            scene->addItem(battle_screen_txt[iter]);
            battle_screen_txt[iter]->setPos(battle_screen_txt[7]->x(), battle_screen_txt[3]->y());
            iter++;

            //stan zalogi
            scene->addItem(battle_screen_txt[iter]);
            battle_screen_txt[iter]->setPos(battle_screen_txt[7]->x(), battle_screen_txt[4]->y());
            iter++;

            //armaty
            scene->addItem(battle_screen_txt[iter]);
            battle_screen_txt[iter]->setPos(battle_screen_txt[7]->x(), battle_screen_txt[5]->y());
            iter++;

            //ammo
            scene->addItem(battle_screen_txt[iter]);
            battle_screen_txt[iter]->setPos(battle_screen_txt[7]->x(), battle_screen_txt[6]->y());

            //elementy paskow
            iter = 0;

            scene->addItem(battle_screen_rect[iter]);
            //battle_screen_rect[iter]->setRect(battle_screen_img[0]->x() + 40, battle_screen_img[0]->y() + 200, 150, 15);
            battle_screen_rect[iter]->setPos(battle_screen_txt[2]->x(), battle_screen_txt[3]->y() + 27);
            iter++;

            scene->addItem(battle_screen_rect[iter]);
            //battle_screen_rect[iter]->setRect(battle_screen_img[0]->x() + 40, battle_screen_img[0]->y() + 238, 150, 15);
            battle_screen_rect[iter]->setPos(battle_screen_txt[2]->x(), battle_screen_txt[4]->y() + 25);
            iter++;

            scene->addItem(battle_screen_rect[iter]);
            //battle_screen_rect[iter]->setRect(battle_screen_img[0]->x() + 410, battle_screen_img[0]->y() + 200, 150, 15);
            battle_screen_rect[iter]->setPos(battle_screen_txt[7]->x(), battle_screen_rect[0]->y());
            iter++;

            scene->addItem(battle_screen_rect[iter]);
            //battle_screen_rect[iter]->setRect(battle_screen_img[0]->x() + 410, battle_screen_img[0]->y() + 238, 150, 15);
            battle_screen_rect[iter]->setPos(battle_screen_txt[7]->x(), battle_screen_rect[1]->y());

            break;
        case 3:
            center_view();
            hide_battle_menu(battle_phase);
            battle_phase = _battle_phase;
            scene->addItem(battle_start_menu[0]);
            scene->addItem(battle_start_menu[1]);
            scene->addItem(battle_start_menu[2]);
            scene->addItem(battle_start_menu[3]);
            scene->addItem(battle_start_menu[4]);
            scene->addItem(sink_abordage_menu_text);
            sink_abordage_menu_text->setPos(battle_start_menu[0]->x() + battle_start_menu[0]->pixmap().width()/2
                                                                      - sink_abordage_menu_text->boundingRect().width()/2,
                                            battle_start_menu[0]->y() + 45);
            break;
        case 5:
            center_view();
            hide_battle_menu(battle_phase);
            battle_phase = _battle_phase;
            scene->addItem(battle_start_menu[0]);
            scene->addItem(battle_start_menu[1]);
            scene->addItem(battle_start_menu[2]);
            scene->addItem(battle_start_menu[3]);
            scene->addItem(battle_start_menu[4]);
            scene->addItem(sink_let_go_menu_text);
            sink_let_go_menu_text->setPos(battle_start_menu[0]->x() + battle_start_menu[0]->pixmap().width()/2
                                                                    - sink_let_go_menu_text->boundingRect().width()/2,
                                          battle_start_menu[0]->y() + 45);
            break;
        case 6:
        case 7:
            center_view();
            hide_battle_menu(4);
            break;
        case 11:
            center_view();
            scene->addItem(battle_start_menu[0]);
            scene->addItem(battle_start_menu[5]);
            battle_start_menu[5]->setPos(battle_start_menu[0]->x() + battle_start_menu[0]->pixmap().width()/2 - battle_start_menu[5]->pixmap().width()/2,
                                         battle_start_menu[0]->y() + 100);
            scene->addItem(battle_start_menu[6]);
            battle_start_menu[6]->setPos(battle_start_menu[5]->x() + battle_start_menu[5]->pixmap().width()/2 - battle_start_menu[6]->pixmap().width()/2,
                                         battle_start_menu[5]->y() + 5);
            scene->addItem(end_battle_menu_text);
            end_battle_menu_text->setPos(battle_start_menu[0]->x() + battle_start_menu[0]->pixmap().width()/2
                                                                   - end_battle_menu_text->boundingRect().width()/2,
                                         battle_start_menu[0]->y() + 45);
            break;
    }
}

void Game::hide_battle_menu(short _battle_phase)
{
    //qDebug() << "Battle phase - " << _battle_phase;
    switch(_battle_phase)
    {
        case 2:
        case 4:
            for(size_t i = 0; i < battle_screen_img.size(); i++)
                scene->removeItem(battle_screen_img[i]);
            for(size_t i = 0; i < battle_screen_txt.size(); i++)
                scene->removeItem(battle_screen_txt[i]);
             for(size_t i = 0; i < battle_screen_rect.size(); i++)
                 scene->removeItem(battle_screen_rect[i]);
            break;
        case 1:
        case 3:
        case 5:
            hide_first_menu();
            break;
        case 11:
            if (battle_phase == 11)
            {
                scene->removeItem(battle_start_menu[0]);
                scene->removeItem(battle_start_menu[5]);
                scene->removeItem(battle_start_menu[6]);
                battle_start_menu[6]->setPixmap(QPixmap(":/tick_off_01.png"));
                scene->removeItem(end_battle_menu_text);
                player->in_battle = false;
                player_at_battle = false;
                battle_phase = 0;
            }
            break;
    }
}

void Game::show_first_menu()
{
    center_view();
    scene->addItem(battle_start_menu[0]);
    battle_start_menu[0]->setPos(scene_x + resolution_x/2 - battle_start_menu[0]->pixmap().width()/2,
                                 scene_y + resolution_y/2 - battle_start_menu[0]->pixmap().height()/2);
    scene->addItem(battle_start_menu[1]);
    battle_start_menu[1]->setPos(battle_start_menu[0]->x() + battle_start_menu[0]->pixmap().width()/5,
                                 battle_start_menu[0]->y() + 5*battle_start_menu[0]->pixmap().height()/9);
    scene->addItem(battle_start_menu[2]);
    battle_start_menu[2]->setPos(battle_start_menu[0]->x() + 4*battle_start_menu[0]->pixmap().width()/5
                                 - battle_start_menu[2]->pixmap().width(),
                                 battle_start_menu[0]->y() + 5*battle_start_menu[0]->pixmap().height()/9);
    scene->addItem(battle_start_menu[3]);
    battle_start_menu[3]->setPos(battle_start_menu[1]->x() + 8, battle_start_menu[1]->y() + 7);
    scene->addItem(battle_start_menu[4]);
    battle_start_menu[4]->setPos(battle_start_menu[2]->x() + 8, battle_start_menu[2]->y() + 7);
    if (battle_phase == 1)
    {
        scene->addItem(battle_start_menu_text);
        battle_start_menu_text->setPos(battle_start_menu[0]->x() + battle_start_menu[0]->pixmap().width()/2
                                                                 - battle_start_menu_text->boundingRect().width()/2,
                                       battle_start_menu[0]->y() + 45);
    }
    if (city_phase == 1)
    {
        scene->addItem(city_start_menu_text);
        city_start_menu_text->setPos(battle_start_menu[0]->x() + battle_start_menu[0]->pixmap().width()/2
                                                               - city_start_menu_text->boundingRect().width()/2,
                                     battle_start_menu[0]->y() + 45);
    }
    if (city_phase == 7)
    {
        scene->addItem(leave_city_text);
        leave_city_text->setPos(battle_start_menu[0]->x() + battle_start_menu[0]->pixmap().width()/2
                                                               - leave_city_text->boundingRect().width()/2,
                                     battle_start_menu[0]->y() + 45);
    }
}

void Game::hide_first_menu()
{
    for (short i=0; i<5; i++)
    {
        scene->removeItem(battle_start_menu[i]);
    }

    battle_start_menu[3]->setPixmap(QPixmap(":/tick_off_01.png"));
    battle_start_menu[4]->setPixmap(QPixmap(":/cross_off_01.png"));

    if (battle_phase == 1)
        scene->removeItem(battle_start_menu_text);
    if (battle_phase == 3)
        scene->removeItem(sink_abordage_menu_text);
    if (battle_phase == 5)
        scene->removeItem(sink_let_go_menu_text);
    if (city_phase == 1)
        scene->removeItem(city_start_menu_text);
    if (city_phase == 7)
        scene->removeItem(leave_city_text);
}

void Game::show_revolt_menu()
{
    reset_timer();
    showing_revolt_menu = true;
    scene->addItem(battle_start_menu[0]);
    battle_start_menu[0]->setPos(scene_x + resolution_x/2 - battle_start_menu[0]->pixmap().width()/2,
                                 scene_y + resolution_y/2 - battle_start_menu[0]->pixmap().height()/2);
    scene->addItem(battle_start_menu[5]);
    battle_start_menu[5]->setPos(scene_x + resolution_x/2 - battle_start_menu[5]->pixmap().width()/2,
                                 battle_start_menu[0]->y() + 100);
    scene->addItem(battle_start_menu[6]);
    battle_start_menu[6]->setPos(battle_start_menu[5]->x() + battle_start_menu[5]->pixmap().width()/2 - battle_start_menu[6]->pixmap().width()/2,
                                 battle_start_menu[5]->y() + 5);
    scene->addItem(revolt_text);
    revolt_text->setPos(battle_start_menu[0]->x() + battle_start_menu[0]->pixmap().width()/2
                                                  - revolt_text->boundingRect().width()/2,
                        battle_start_menu[0]->y() + 45);
}

void Game::hide_revolt_menu()
{
    showing_revolt_menu = false;
    scene->removeItem(battle_start_menu[0]);
    scene->removeItem(battle_start_menu[5]);
    scene->removeItem(battle_start_menu[6]);
    scene->removeItem(revolt_text);
}

void Game::show_npc_info(NPC *_ship)
{
    /*foreach (Cargo * cargo, _ship->get_goods())
        qDebug() << cargo->get_name() << " - " << cargo->get_amount();*/
    // placing info_bar
    if (_ship->get_x() < scene_x + npc_info_bar->pixmap().width()/2)
        npc_info_bar_x = _ship->get_x() - _ship->get_sprite_width()/2;
    else
    if (_ship->get_x() > scene_x + resolution_x - npc_info_bar->pixmap().width()/2)
        npc_info_bar_x = _ship->get_x() + _ship->get_sprite_width()/2 - npc_info_bar->pixmap().width();
    else
        npc_info_bar_x = _ship->get_x() - npc_info_bar->pixmap().width()/2;

    if (_ship->get_y() < scene_y + npc_info_bar->pixmap().height() + _ship->get_sprite_height()/2)
        npc_info_bar_y = _ship->get_y() + _ship->get_sprite_height()/2;
    else
        npc_info_bar_y = _ship->get_y() - _ship->get_sprite_height()/2 - npc_info_bar->pixmap().height();

    npc_info_bar->setPos(npc_info_bar_x, npc_info_bar_y);

    //ustawianie napisow
    info_name_text->setPlainText(_ship->get_name());
    info_model_text->setPlainText(_ship->get_fraction() + QString(" ") + _ship->get_model_name());
    info_health_text->setPlainText(QString("health - " + QString::number(_ship->get_health())));
    info_crew_text->setPlainText(QString("crew - " + QString::number(_ship->get_crew())));

    //ustawianie pozycji elementow
    info_name_text->setPos(npc_info_bar_x, npc_info_bar_y);
    info_model_text->setPos(npc_info_bar_x, npc_info_bar_y + 20);
    info_health_text->setPos(npc_info_bar_x, npc_info_bar_y + 39);
    info_crew_text->setPos(npc_info_bar_x, npc_info_bar_y + 75);

    //npc_status_bars[0]->setPos(npc_info_bar_x + 10, npc_info_bar_y + 60);
    npc_status_bars[0]->setRect(npc_info_bar_x + 10, npc_info_bar_y + 65, (int)(100.0*(float)_ship->get_health()/(float)_ship->get_max_health()), 12);
    //map_rect->setRect(x,y,w,h);
    npc_status_bars[1]->setPos(npc_info_bar_x + 10, npc_info_bar_y + 65);
    //npc_status_bars[2]->setPos(npc_info_bar_x + 10, npc_info_bar_y + 100);
    npc_status_bars[2]->setRect(npc_info_bar_x + 10, npc_info_bar_y + 100, (int)(100.0*(float)_ship->get_crew()/(float)_ship->get_max_crew()), 12);
    npc_status_bars[3]->setPos(npc_info_bar_x + 10, npc_info_bar_y + 100);

    if (!showing_npc_info && !battle_phase)
    {
        scene->addItem(npc_info_bar);
        scene->addItem(info_name_text);
        scene->addItem(info_model_text);
        scene->addItem(info_crew_text);
        scene->addItem(info_health_text);
        scene->addItem(npc_status_bars[0]);
        scene->addItem(npc_status_bars[1]);
        scene->addItem(npc_status_bars[2]);
        scene->addItem(npc_status_bars[3]);
        showing_npc_info = true;
    }
}

void Game::hide_npc_info()
{
    showing_npc_info = false;
    scene->removeItem(npc_info_bar);
    scene->removeItem(info_name_text);
    scene->removeItem(info_model_text);
    scene->removeItem(info_crew_text);
    scene->removeItem(info_health_text);
    for (short i = 0; i <4; i++)
        scene->removeItem(npc_status_bars[i]);
}

void Game::create_new_npc()
{
    npc_ships.push_back(new NPC());
    scene->addItem(npc_ships[npc_ships.size() - 1]);
    connect(npc_ships[npc_ships.size() - 1], SIGNAL(delete_npc(NPC *)),
            this, SLOT(delete_npc(NPC *)));
    connect (timer, SIGNAL(timeout()), npc_ships[npc_ships.size() - 1], SLOT(move_to_next_location()));
    connect (npc_ships[npc_ships.size() - 1], SIGNAL(send_info(NPC *)), this, SLOT(show_npc_info(NPC *)));
    connect (npc_ships[npc_ships.size() - 1], SIGNAL(hide_info()), this, SLOT(hide_npc_info()));
    scene->addItem(npc_ships[npc_ships.size() - 1]->flag);
}

void Game::mouse_moved()
{
    if (city_phase == 4)
    {
        if (shipyard_img[1]->isUnderMouse())
            city_menu_text[6]->setDefaultTextColor(Qt::red);
        else
            city_menu_text[6]->setDefaultTextColor(Qt::white);
        for (short i = 3; i < 8; i++)
            if (shipyard_img[i]->isUnderMouse())
                shipyard_img[i]->setPixmap(QPixmap(":/plus_on_02.png"));
            else
                shipyard_img[i]->setPixmap(QPixmap(":/plus_off_02.png"));
        for (short i = 8; i < 11; i++)
            if (shipyard_img[i]->isUnderMouse())
                shipyard_img[i]->setPixmap(QPixmap(":/minus_on_02.png"));
            else
                shipyard_img[i]->setPixmap(QPixmap(":/minus_off_02.png"));
    }

    // obszar menu dla rozpoczęcia walki, landowania w mieście i wypływaniu z miasta
    if ((city_phase == 1 || city_phase == 7 || battle_phase == 1 || battle_phase == 3 || battle_phase == 5) && !menu_bool)
    {
        if (battle_start_menu[1]->isUnderMouse())
            battle_start_menu[3]->setPixmap(QPixmap(":/tick_on_01.png"));
        else
            battle_start_menu[3]->setPixmap(QPixmap(":/tick_off_01.png"));

        if (battle_start_menu[2]->isUnderMouse())
            battle_start_menu[4]->setPixmap(QPixmap(":/cross_on_01.png"));
        else
            battle_start_menu[4]->setPixmap(QPixmap(":/cross_off_01.png"));
    }

    // obszar podczas walki statkami lub abordażu
    if (battle_phase == 2 || battle_phase == 4)
    {
        if(battle_screen_img[1]->isUnderMouse())
        {
            battle_screen_txt[1]->setDefaultTextColor(Qt::red);
        }
        else
        {
            battle_screen_txt[1]->setDefaultTextColor(Qt::white);
        }
    }

    // obszar ostatniego powiadomienia walki i menu buntu
    if (battle_phase == 11 || showing_revolt_menu)
    {
        if (battle_start_menu[5]->isUnderMouse())
            battle_start_menu[6]->setPixmap(QPixmap(":/tick_on_01.png"));
        else
            battle_start_menu[6]->setPixmap(QPixmap(":/tick_off_01.png"));
    }

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
    if (view->get_x() > resolution_x/2 + 124 && view->get_x() < resolution_x/2 +220 && view->get_y() < resolution_y - 10 && view->get_y() > resolution_y - 38)
        hud_temp_bool[4] = 1;
    if (!(view->get_x() > resolution_x/2 +124  && view->get_x() < resolution_x/2 +220 && view->get_y() < resolution_y - 10 && view->get_y() > resolution_y - 38))
        hud_temp_bool[4] = 0;

    //obszar przycisku menu
    if (hud_img[5]->isUnderMouse())
    //if (view->get_x() > 10 && view->get_x() < 150 && view->get_y() > 5 && view->get_y() < 40)
        hud_txt[hud_txt.size()-2]->setDefaultTextColor(Qt::white);
    else
    //if (!(view->get_x() > 10 && view->get_x() < 150 && view->get_y() > 5 && view->get_y() < 40))
        hud_txt[hud_txt.size()-2]->setDefaultTextColor(Qt::black);

    //obsługa menu
    if (menu_bool)
    {
        /*
        if (view->get_x() > resolution_x/2 - 120 && view->get_x() < resolution_x/2 +120 && view->get_y() > resolution_y/2 - 140 && view->get_y() < resolution_y/2 -100)
            menu_text[0]->setDefaultTextColor(Qt::red);
        if (!(view->get_x() > resolution_x/2 - 120 && view->get_x() < resolution_x/2 + 120 && view->get_y() > resolution_y/2 - 140 && view->get_y() < resolution_y/2 -100))
            menu_text[0]->setDefaultTextColor(Qt::white);

        if (view->get_x() > resolution_x/2 - 200 && view->get_x() < resolution_x/2 +200 && view->get_y() > resolution_y/2 - 75 && view->get_y() < resolution_y/2 -25)
            menu_text[1]->setDefaultTextColor(Qt::red);
        if (!(view->get_x() > resolution_x/2 - 200 && view->get_x() < resolution_x/2 +200 && view->get_y() > resolution_y/2 - 75 && view->get_y() < resolution_y/2 -25))
            menu_text[1]->setDefaultTextColor(Qt::white);
            */
        //if (menu_text[2]->isUnderMouse())
        /*if (view->get_x() > resolution_x/2 - 120 && view->get_x() < resolution_x/2 +120 && view->get_y() > resolution_y/2 - 10 && view->get_y() < resolution_y/2 + 40)
            menu_text[2]->setDefaultTextColor(Qt::red);
        else
        //if (!(view->get_x() > resolution_x/2 - 200 && view->get_x() < resolution_x/2 +200 && view->get_y() > resolution_y/2 - 10 && view->get_y() < resolution_y/2 + 40))
            menu_text[2]->setDefaultTextColor(Qt::white);

        //if (menu_text[3]->isUnderMouse())
        if (view->get_x() > resolution_x/2 - 120 && view->get_x() < resolution_x/2 +120 && view->get_y() > resolution_y/2 + 45 && view->get_y() < resolution_y/2 + 95)
            menu_text[3]->setDefaultTextColor(Qt::red);
        else
        //if (!(view->get_x() > resolution_x/2 - 200 && view->get_x() < resolution_x/2 +200 && view->get_y() > resolution_y/2 + 45 && view->get_y() < resolution_y/2 + 95))
            menu_text[3]->setDefaultTextColor(Qt::white);

        //if (menu_text[4]->isUnderMouse())
        if (view->get_x() > resolution_x/2 - 120 && view->get_x() < resolution_x/2 +120 && view->get_y() > resolution_y/2 + 155 && view->get_y() < resolution_y/2 + 200)
            menu_text[4]->setDefaultTextColor(Qt::red);
        else
        //if (!(view->get_x() > resolution_x/2 - 200 && view->get_x() < resolution_x/2 +200 && view->get_y() > resolution_y/2 + 155 && view->get_y() < resolution_y/2 + 200))
            menu_text[4]->setDefaultTextColor(Qt::white);*/
        for (short i = 2; i < 5; i++)
        {
            if (menu_buttons[i]->isUnderMouse())
                menu_text[i]->setDefaultTextColor(Qt::red);
            else
                menu_text[i]->setDefaultTextColor(Qt::white);
        }
    }

    if (player_in_city)
    {
        for (short i = 1; i < 5; i++)
        {
            if (menu_buttons[i]->isUnderMouse())
                city_menu_text[i]->setDefaultTextColor(Qt::red);
            else
                city_menu_text[i]->setDefaultTextColor(Qt::white);
        }
    }

    //obszar ładowni
    if (view->get_x() > resolution_x/2 - 310 && view->get_x() < resolution_x/2 -220 && view->get_y() > 10 && view->get_y() < 80)
    {
        hud_temp_bool[5] = 1;
        if (player->get_hold_size())
            hud_temp_txt[5]->setPlainText(QString(player->get_goods()[0]->get_name()));
        else
            hud_temp_txt[5]->setPlainText(QString("locked slot"));
    }
    else if (view->get_x() > resolution_x/2 - 215 && view->get_x() < resolution_x/2 -135 && view->get_y() > 10 && view->get_y() < 80)
    {
        hud_temp_bool[5] = 1;
        if (player->get_hold_size() > 1)
            hud_temp_txt[5]->setPlainText(QString(player->get_goods()[1]->get_name()));
        else
            hud_temp_txt[5]->setPlainText(QString("locked slot"));
    }
    else if (view->get_x() > resolution_x/2 - 130 && view->get_x() < resolution_x/2 - 50 && view->get_y() > 10 && view->get_y() < 80)
    {
        hud_temp_bool[5] = 1;
        if (player->get_hold_size() > 2)
            hud_temp_txt[5]->setPlainText(QString(player->get_goods()[2]->get_name()));
        else
            hud_temp_txt[5]->setPlainText(QString("locked slot"));
    }
    else if (view->get_x() > resolution_x/2 - 50 && view->get_x() < resolution_x/2 +35 && view->get_y() > 10 && view->get_y() < 80)
    {
        hud_temp_bool[5] = 1;
        if (player->get_hold_size() > 3)
            hud_temp_txt[5]->setPlainText(QString(player->get_goods()[3]->get_name()));
        else
            hud_temp_txt[5]->setPlainText(QString("locked slot"));
    }
    else if (view->get_x() > resolution_x/2 + 35 && view->get_x() < resolution_x/2 + 123 && view->get_y() > 10 && view->get_y() < 80)
    {
        hud_temp_bool[5] = 1;
        if (player->get_hold_size() > 4)
            hud_temp_txt[5]->setPlainText(QString(player->get_goods()[5]->get_name()));
        else
            hud_temp_txt[5]->setPlainText(QString("locked slot"));
    }
    else if (view->get_x() > resolution_x/2 + 123 && view->get_x() < resolution_x/2 + 211 && view->get_y() > 10 && view->get_y() < 80)
    {
        hud_temp_bool[5] = 1;
        if (player->get_hold_size() > 5)
            hud_temp_txt[5]->setPlainText(QString(player->get_goods()[6]->get_name()));
        else
            hud_temp_txt[5]->setPlainText(QString("locked slot"));
    }
    else if (view->get_x() > resolution_x/2 + 211 && view->get_x() < resolution_x/2 + 299 && view->get_y() > 10 && view->get_y() < 80)
    {
        hud_temp_bool[5] = 1;
        if (player->get_hold_size() > 6)
            hud_temp_txt[5]->setPlainText(QString(player->get_goods()[6]->get_name()));
        else
            hud_temp_txt[5]->setPlainText(QString("locked slot"));
    }

    //obszar prawego górnego HUD'u
    else if (view->get_x() > resolution_x - 155 && view->get_y() < 35)
    {
        hud_temp_bool[5] = 1;
        hud_temp_txt[5]->setPlainText(QString("Ship name"));
    }
    else if (view->get_x() > resolution_x - 100 && view->get_y() < 70)
    {
        hud_temp_bool[5] = 1;
        hud_temp_txt[5]->setPlainText(QString("Cannons"));
    }
    else if (view->get_x() > resolution_x - 100 && view->get_y() < 100)
    {
        hud_temp_bool[5] = 1;
        hud_temp_txt[5]->setPlainText(QString("Ammunition"));
    }
    else
    {
        hud_temp_bool[5] = 0;
        hud_temp_txt[5]->setPlainText(QString("Description"));
    }
}

void Game::mouse_pressed()
{
    // czy chcę gracz wejść w miasto
    if (city_phase == 1 && !menu_bool && !clicked)
    {
        if (battle_start_menu[2]->isUnderMouse())
        {
            clicked = true;
            hide_city_menu(city_phase);
            leave_city();
        }
        if (battle_start_menu[1]->isUnderMouse())
        {
            clicked = true;
            hide_city_menu(city_phase);
            city_phase = 2;
            player_in_city = true;
            player->lower_the_sails();
            show_city_menu(city_phase);
        }
    }

    // obsługa głownego menu miasta
    if (city_phase == 2)
    {
        if (menu_buttons[4]->isUnderMouse())
        {
            //leave_city();
            hide_city_menu(city_phase);
            city_phase = 7;
            show_city_menu(city_phase);
        }
        if (menu_buttons[3]->isUnderMouse())
        {
            hide_city_menu(city_phase);
            city_phase = 4;
            show_city_menu(city_phase);
        }
    }

    // czy gracz chcę wyjść z miasta
    if (city_phase == 7 && !menu_bool && !clicked)
    {
        if (battle_start_menu[1]->isUnderMouse())
        {
            clicked = true;
            hide_city_menu(city_phase);
            leave_city();
        }
        if (battle_start_menu[2]->isUnderMouse())
        {
            clicked = true;
            hide_city_menu(city_phase);
            city_phase = 2;
            show_city_menu(city_phase);
        }
    }

    // obsługa stoczni
    if (city_phase == 4 && !clicked)
    {
        // wyjście ze stoczni
        if (shipyard_img[1]->isUnderMouse())
        {
            clicked = true;
            hide_city_menu(city_phase);
            city_phase = 2;
            show_city_menu(city_phase);
        }

        // zmiana zdrowia
        if (shipyard_img[5]->isUnderMouse() && player->get_health() < player->get_max_health())
        {
            player->set_health(player->get_health() + 1);
            shipyard_txt[3]->setPlainText(QString::number(short(100 * double(player->get_health()) /
                                                                             player->get_max_health())) + QString("%"));
        }
        if (shipyard_img[8]->isUnderMouse() && player->get_health() > player_city_start_health)
        {
            player->set_health(player->get_health() - 1);
            shipyard_txt[3]->setPlainText(QString::number(short(100 * double(player->get_health()) /
                                                                             player->get_max_health())) + QString("%"));
        }
        // zmiana armat
        if (shipyard_img[6]->isUnderMouse() && player->get_cannons() < player->get_max_cannons())
        {
            player->set_cannons(player->get_cannons() + 1);
            shipyard_txt[4]->setPlainText(QString::number(player->get_cannons()));
        }
        if (shipyard_img[9]->isUnderMouse() && player->get_cannons() > 0)
        {
            player->set_cannons(player->get_cannons() - 1);
            shipyard_txt[4]->setPlainText(QString::number(player->get_cannons()));
        }

        // zmiana armat
        if (shipyard_img[7]->isUnderMouse() && player->get_ammo() < player->get_max_ammo())
        {
            player->set_ammo(player->get_ammo() + 1);
            shipyard_txt[5]->setPlainText(QString::number(player->get_ammo()));
        }
        if (shipyard_img[10]->isUnderMouse() && player->get_ammo() > 0)
        {
            player->set_ammo(player->get_ammo() - 1);
            shipyard_txt[5]->setPlainText(QString::number(player->get_ammo()));
        }

        //kupowanie statkow
        if (shipyard_img[3]->isUnderMouse())
            player->buy_new_ship(actual_city->get_selling_ship_model(0));
        if (shipyard_img[4]->isUnderMouse())
            player->buy_new_ship(actual_city->get_selling_ship_model(1));

        center_view();
    }

    // obsługa battle menu
    if (battle_phase == 1 && !menu_bool && !clicked)
    {
        if (battle_start_menu[2]->isUnderMouse())
        {
            clicked = true;
            hide_battle_menu(battle_phase);
            end_player_battle(0);
        }
        if (battle_start_menu[1]->isUnderMouse())
        {
            clicked = true;
            hide_battle_menu(battle_phase);
            battle_phase = 2;
            show_battle_menu(battle_phase);
            battle(battle_phase);
        }
    }

    // obsługa walki statkami lub abordażu
    if ((battle_phase == 2 || battle_phase == 4) && !clicked)
    {
        if (battle_screen_img[1]->isUnderMouse())
        {
            clicked = true;
            hide_battle_menu(battle_phase);
            battle_phase = 8;
            emit run_away();
        }
    }

    // czy chcę gracz zacząć abordaż
    if (battle_phase == 3 && !clicked)
    {
        if (battle_start_menu[2]->isUnderMouse())
        {
            clicked = true;
            hide_battle_menu(battle_phase);
            battle_phase = 6;
            emit sink_abordage(battle_phase);
        }
        if (battle_start_menu[1]->isUnderMouse())
        {
            clicked = true;
            hide_battle_menu(battle_phase);
            battle_phase = 4;
            show_battle_menu(battle_phase);
            emit sink_abordage(battle_phase);
        }
    }

    // czy chcę gracz odpuścić statek po wygranej
    if (battle_phase == 5 && !clicked)
    {
        if (battle_start_menu[2]->isUnderMouse())
        {
            clicked = true;
            hide_battle_menu(battle_phase);
            battle_phase = 6;
            emit sink_let_go(false);
        }
        if (battle_start_menu[1]->isUnderMouse())
        {
            clicked = true;
            hide_battle_menu(battle_phase);
            battle_phase = 7;
            emit sink_let_go(true);
        }
    }

    // potwierdzenie końca walki na morzu
    if (battle_phase == 11 && !clicked)
    {
        if (battle_start_menu[5]->isUnderMouse())
        {
            clicked = true;
            hide_battle_menu(battle_phase);
            reset_timer();
        }
    }

    // obsługa menu buntu
    if (showing_revolt_menu && !menu_bool && !clicked)
    {
        if (battle_start_menu[5]->isUnderMouse())
        {
            clicked = true;
            hide_revolt_menu();
            reset_timer();
        }
    }

    //obszar przycisku menu
    if (hud_img[5]->isUnderMouse() && !clicked && !player_at_battle && !showing_revolt_menu && !player->in_city)
    //if (view->get_x() > 10 && view->get_x() < 150 && view->get_y() > 5 && view->get_y() < 40)
    {
        clicked = true;
        show_menu();
    }

    //obsługa menu
    if (menu_bool)
    {
        clicked = true;
        if (menu_buttons[3]->isUnderMouse())
        //if (view->get_x() > resolution_x/2 - 200 && view->get_x() < resolution_x/2 +200 && view->get_y() > resolution_y/2 + 45 && view->get_y() < resolution_y/2 + 95)
            QApplication::quit();

        if (menu_buttons[4]->isUnderMouse())
        //if (view->get_x() > resolution_x/2 - 200 && view->get_x() < resolution_x/2 +200 && view->get_y() > resolution_y/2 + 155 && view->get_y() < resolution_y/2 + 200)
            show_menu();
    }
}

void Game::mouse_released()
{
    if (clicked)
    {
        clicked = false;
    }
}

void Game::reset_timer()
{
    start_stop();
}

void Game::delete_npc(NPC *_ship)
{
    scene->removeItem(_ship->flag);
    scene->removeItem(_ship);
}

void Game::esc_pressed()
{
    if (!player_at_battle && !showing_revolt_menu && !player->in_city)
        show_menu();
}
