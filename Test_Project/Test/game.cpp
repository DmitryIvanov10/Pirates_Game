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
    if (!player_at_battle)
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

    //nazwa statku
    hud_txt[8]->setPlainText(QString(player->get_model_name()));
    hud_txt[8]->setPos(scene_x + resolution_x - 145, scene_y + 3);

    //tekst menu
    hud_txt[9]->setPos(scene_x + 45, scene_y + 10);


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
                hud_cargo_txt[iterate]->setPos(scene_x + resolution_x/2  - 166, scene_y + 61);
            }
            if(iterate == 2)
            {
                hud_cargo_txt[iterate]->setPos(scene_x + resolution_x/2  - 78, scene_y + 61);
            }
            if(iterate == 3)
            {
                hud_cargo_txt[iterate]->setPos(scene_x + resolution_x/2  + 12, scene_y + 61);
            }
            if(iterate == 4)
            {
                hud_cargo_txt[iterate]->setPos(scene_x + resolution_x/2  + 100, scene_y + 61);
            }
            if(iterate == 5)
            {
                hud_cargo_txt[iterate]->setPos(scene_x + resolution_x/2  + 188, scene_y + 61);
            }
            if(iterate == 6)
            {
                hud_cargo_txt[iterate]->setPos(scene_x + resolution_x/2  + 276, scene_y + 61);
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
    map_rect->setRect(scene_x + 15 + 265 * ((float)scene_x / (8196 + 2 * border_x)), scene_y + resolution_y - 156 + 148 * ((float)scene_y / (4608 + 2* border_y)), (int)(267 * ((float)resolution_x / (8196 + 2* border_x))), (int)(151 * ((float)resolution_y / (4608 + 2* border_y))));
    if (battle_phase)
    {
        info_health_text->setPlainText(QString("NPC health - " + QString::number(battle_ship->get_health())));
        info_crew_text->setPlainText(QString("NPC crew - " + QString::number(battle_ship->get_crew())));
    }
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
    /*if (!player_at_battle)
    {
        player_at_battle = true;
        player->in_battle = true;
        battles.push_back(new Battle(player, _ship));
        connect(battles[battles.size()-1], SIGNAL(finish_battle()), this, SLOT(end_player_battle()));
        connect(battles[battles.size()-1], SIGNAL(finish_battle()), _ship, SLOT(reset()));
        connect(battles[battles.size()-1], SIGNAL(lost(short)), player, SLOT(on_boat(short)));
    }*/
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
    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/Message_bar_02.png"));
    iterate++;

    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/Small_button_01.png"));
    iterate++;

    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/Small_button_01.png"));
    iterate++;

    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/tick_off_01.png"));
    iterate++;

    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/cross_off_01.png"));
    iterate++;

    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/tick_on_01.png"));
    iterate++;

    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/cross_on_01.png"));
    iterate++;

    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/big_button_01.png"));
    iterate++;

    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/tick_off_01.png"));
    iterate++;

    battle_start_menu.push_back(new QGraphicsPixmapItem());
    battle_start_menu[iterate]->setPixmap(QPixmap(":/tick_on_01.png"));

    battle_start_menu_text->setPlainText(QString("Would you like to start a battle?"));
    battle_start_menu_text->setDefaultTextColor(Qt::white);
    battle_start_menu_text->setFont(QFont("times", 12));

    end_battle_menu_text->setDefaultTextColor(Qt::white);
    end_battle_menu_text->setFont(QFont("times", 12));


    //elementy walki morskiej
    //czesc graficzna
    iterate = 0;

    battle_screen_img.push_back(new QGraphicsPixmapItem());
    battle_screen_img[0]->setPixmap(QPixmap(":/battle_screen_02.png"));
    iterate++;

    battle_screen_img.push_back(new QGraphicsPixmapItem());
    battle_screen_img[0]->setPixmap(QPixmap(":/medium_button_01.png"));
    iterate++;


    //elementy fazy abordażu
    sink_abordage_menu_text->setPlainText(QString("Would you like to start abordage?"));
    sink_abordage_menu_text->setDefaultTextColor(Qt::white);
    sink_abordage_menu_text->setFont(QFont("times", 12));

    sink_let_go_menu_text->setPlainText(QString("Would you like to let the ship go?"));
    sink_let_go_menu_text->setDefaultTextColor(Qt::white);
    sink_let_go_menu_text->setFont(QFont("times", 12));


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

    //tekst
    for(int i = 0; i < 6; i++)
    {
        menu_text.push_back(new QGraphicsTextItem());
        menu_text[i]->setFont(QFont("times", 16));
        menu_text[i]->setDefaultTextColor(Qt::white);
    }


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

void Game::show_menu()
{
    if (!battle_phase)
        reset_timer();
    if (!menu_bool)
    {
        menu_bar->setPixmap(QPixmap(":/Menu_bar_02.png"));
        scene->addItem(menu_bar);
        menu_bar->setPos(scene_x + resolution_x/2 - menu_bar->pixmap().width()/2, scene_y + resolution_y/2 - menu_bar->pixmap().height()/2);

        menu_text[0]->setPlainText(QString("Save game"));
        scene->addItem(menu_text[0]);
        menu_text[0]->setPos(scene_x + resolution_x/2 - 50, scene_y + resolution_y/2 - 136);

        menu_text[0]->setDefaultTextColor(Qt::darkGray);

        menu_text[1]->setPlainText(QString("Load game"));
        scene->addItem(menu_text[1]);
        menu_text[1]->setPos(scene_x + resolution_x/2 - 50, scene_y + resolution_y/2 - 72);

        menu_text[1]->setDefaultTextColor(Qt::darkGray);

        menu_text[2]->setPlainText(QString("Options"));
        scene->addItem(menu_text[2]);
        menu_text[2]->setPos(scene_x + resolution_x/2 - 37, scene_y + resolution_y/2 - 10);

        menu_text[3]->setPlainText(QString("Exit game"));
        scene->addItem(menu_text[3]);
        menu_text[3]->setPos(scene_x + resolution_x/2 - 50, scene_y + resolution_y/2 + 50);

        menu_text[4]->setPlainText(QString("Continue"));
        scene->addItem(menu_text[4]);
        menu_text[4]->setPos(scene_x + resolution_x/2 - 40, scene_y + resolution_y/2 + 158);

        menu_text[5]->setPlainText(QString("Main menu"));
        scene->addItem(menu_text[5]);
        menu_text[5]->setPos(scene_x + resolution_x/2 - 40, scene_y + resolution_y/2 - 205);

        menu_text[5]->setDefaultTextColor(Qt::darkGray);
        menu_text[5]->setFont(QFont("times", 12));
    }
    else
    {
        scene->removeItem(menu_bar);
        for(int i = 0; i < 6; i++)
            scene->removeItem(menu_text[i]);
    }
    menu_bool = !menu_bool;
}

void Game::battle(short _battle_phase)
{
    switch(_battle_phase)
    {
        case 1:
            show_battle_menu(1);
            break;
        case 2:
            if (!player_at_battle)
            {
                player_at_battle = true;
                player->in_battle = true;
                battles.push_back(new Battle(player, battle_ship));
                connect(battles[battles.size()-1], SIGNAL(finish_battle(short)), this, SLOT(end_player_battle(short)));
                connect(battles[battles.size()-1], SIGNAL(finish_battle(short)), battle_ship, SLOT(reset()));
                connect(battles[battles.size()-1], SIGNAL(update_info()), this, SLOT(center_view()));
                connect(battles[battles.size()-1], SIGNAL(lost(short)), player, SLOT(on_boat(short)));
                connect(battles[battles.size()-1], SIGNAL(sink_abordage(short)), this, SLOT(show_battle_menu(short)));
                connect(this, SIGNAL(sink_abordage(short)), battles[battles.size()-1], SLOT(after_sea_battle(short)));
                connect(battles[battles.size()-1], SIGNAL(sink_let_go(short)), this, SLOT(show_battle_menu(short)));
                connect(this, SIGNAL(sink_let_go(bool)), battles[battles.size()-1], SLOT(win_abordage(bool)));
            }
            break;
    }
}

void Game::show_battle_menu(short _battle_phase)
{
    /*
     * 0 - no battle
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
*/
    switch(_battle_phase)
    {
        case 1:
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
            battle_start_menu[5]->setPos(battle_start_menu[3]->x(), battle_start_menu[3]->y());
            battle_start_menu[6]->setPos(battle_start_menu[4]->x(), battle_start_menu[4]->y());
            scene->addItem(battle_start_menu_text);
            battle_start_menu_text->setPos(battle_start_menu[0]->x() + 60, battle_start_menu[0]->y() + 45);
            info_crew_text->setPos(battle_start_menu[0]->x() + 115, battle_start_menu[0]->y() + 45);
            info_health_text->setPos(battle_start_menu[0]->x() + 115, battle_start_menu[0]->y() + 45);
            break;
        case 2:
            center_view();
            scene->addItem(battle_start_menu[0]);
            scene->addItem(info_health_text);
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
            sink_abordage_menu_text->setPos(battle_start_menu[0]->x() + 54, battle_start_menu[0]->y() + 45);
            break;
        case 4:
            center_view();
            scene->addItem(battle_start_menu[0]);
            scene->addItem(info_crew_text);
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
            sink_let_go_menu_text->setPos(battle_start_menu[0]->x() + 54, battle_start_menu[0]->y() + 45);
            break;
        case 6:
        case 7:
            center_view();
            hide_battle_menu(4);
            break;
        case 11:
            center_view();
            scene->addItem(battle_start_menu[0]);
            scene->addItem(battle_start_menu[7]);
            battle_start_menu[7]->setPos(scene_x + resolution_x/2 - battle_start_menu[7]->pixmap().width()/2,
                                         battle_start_menu[0]->y() + 100);
            scene->addItem(battle_start_menu[8]);
            battle_start_menu[8]->setPos(battle_start_menu[7]->x() + battle_start_menu[7]->pixmap().width()/2 - battle_start_menu[3]->pixmap().width()/2,
                                         battle_start_menu[1]->y() + 11);
            battle_start_menu[9]->setPos(battle_start_menu[8]->x(), battle_start_menu[8]->y());
            scene->addItem(end_battle_menu_text);
            end_battle_menu_text->setPos(battle_start_menu[0]->x() + 40, battle_start_menu[0]->y() + 45);
            break;
    }
}

void Game::hide_battle_menu(short _battle_phase)
{
    //qDebug() << "Battle phase - " << _battle_phase;
    switch(_battle_phase)
    {
        case 1:
        case 3:
        case 5:
            for (size_t i=0; i<5; i++)
            {
                //qDebug() << "Removing " << i << " item.";
                scene->removeItem(battle_start_menu[i]);
            }
            if (element1_in_scene)
            {
                //qDebug() << "Removing 1 item.";
                scene->removeItem(battle_start_menu[5]);
                element1_in_scene = false;
            }
            if (element2_in_scene)
            {
                //qDebug() << "Removing 2 item.";
                scene->removeItem(battle_start_menu[6]);
                element2_in_scene = false;
            }
            if (_battle_phase == 1){
                //qDebug() << "Removing start menu text";
                scene->removeItem(battle_start_menu_text);}
            if (_battle_phase == 3){
                //qDebug() << "Removing sink abordage menu text.";
                scene->removeItem(sink_abordage_menu_text);}
            if (_battle_phase == 5) {
                //qDebug() << "Removing sink let go menu text";
                scene->removeItem(sink_let_go_menu_text);}
            break;
        case 2:
            //qDebug() << "Removing main menu";
            scene->removeItem(battle_start_menu[0]);
            //qDebug() << "Removing health text";
            scene->removeItem(info_health_text);
            break;
        case 4:
            //qDebug() << "removing main menu";
            scene->removeItem(battle_start_menu[0]);
            //qDebug() << "Removing crew text";
            scene->removeItem(info_crew_text);
        case 11:
            if (battle_phase == 11)
            {
                //qDebug() << "Removing main menu";
                scene->removeItem(battle_start_menu[0]);
                //qDebug() << "Removing button";
                scene->removeItem(battle_start_menu[7]);
                //qDebug() << "Removing off click";
                scene->removeItem(battle_start_menu[8]);
                if (element1_in_scene)
                {
                    //qDebug() << "Removing on click";
                    scene->removeItem(battle_start_menu[9]);
                    element1_in_scene = false;
                }
                //qDebug() << "Removing end battle text.";
                scene->removeItem(end_battle_menu_text);
                player->in_battle = false;
                player_at_battle = false;
                battle_phase = 0;
            }
            break;
    }
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
    scene->removeItem(npc_status_bars[0]);
    scene->removeItem(npc_status_bars[1]);
    scene->removeItem(npc_status_bars[2]);
    scene->removeItem(npc_status_bars[3]);
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
    // obszar menu dla rozpoczęcia walki
    if (battle_phase == 1 || battle_phase == 3 || battle_phase == 5)
    {
        if (battle_start_menu[1]->isUnderMouse() && !element1_in_scene)
        {
            scene->addItem(battle_start_menu[5]);
            element1_in_scene = true;
        }
        if (!battle_start_menu[1]->isUnderMouse() && element1_in_scene)
        {
            scene->removeItem(battle_start_menu[5]);
            element1_in_scene = false;
        }

        if (battle_start_menu[2]->isUnderMouse() && !element2_in_scene)
        {
            scene->addItem(battle_start_menu[6]);
            element2_in_scene = true;
        }
        if (!battle_start_menu[2]->isUnderMouse() && element2_in_scene)
        {
            scene->removeItem(battle_start_menu[6]);
            element2_in_scene = false;
        }
    }

    if (battle_phase == 11)
    {
        if (battle_start_menu[7]->isUnderMouse() && !element1_in_scene)
        {
            scene->addItem(battle_start_menu[9]);
            element1_in_scene = true;
        }
        if (!battle_start_menu[7]->isUnderMouse() && element1_in_scene)
        {
            scene->removeItem(battle_start_menu[9]);
            element1_in_scene = false;
        }
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
        hud_txt[hud_txt.size()-1]->setDefaultTextColor(Qt::white);
    else
    //if (!(view->get_x() > 10 && view->get_x() < 150 && view->get_y() > 5 && view->get_y() < 40))
        hud_txt[hud_txt.size()-1]->setDefaultTextColor(Qt::black);

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
        if (view->get_x() > resolution_x/2 - 120 && view->get_x() < resolution_x/2 +120 && view->get_y() > resolution_y/2 - 10 && view->get_y() < resolution_y/2 + 40)
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
            menu_text[4]->setDefaultTextColor(Qt::white);
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
    // obsługa battle menu
    if (battle_phase == 1)
    {
        if (battle_start_menu[2]->isUnderMouse() && !clicked)
        {
            clicked = true;
            hide_battle_menu(battle_phase);
            end_player_battle(0);
        }
        if (battle_start_menu[1]->isUnderMouse() && !clicked)
        {
            clicked = true;
            hide_battle_menu(battle_phase);
            battle_phase = 2;
            show_battle_menu(battle_phase);
            battle(battle_phase);
        }
    }

    if (battle_phase == 3)
    {
        if (battle_start_menu[2]->isUnderMouse() && !clicked)
        {
            clicked = true;
            hide_battle_menu(battle_phase);
            battle_phase = 6;
            emit sink_abordage(battle_phase);
        }
        if (battle_start_menu[1]->isUnderMouse() && !clicked)
        {
            clicked = true;
            hide_battle_menu(battle_phase);
            battle_phase = 4;
            show_battle_menu(battle_phase);
            emit sink_abordage(battle_phase);
        }
    }

    if (battle_phase == 5)
    {
        if (battle_start_menu[2]->isUnderMouse() && !clicked)
        {
            clicked = true;
            hide_battle_menu(battle_phase);
            battle_phase = 6;
            emit sink_let_go(false);
        }
        if (battle_start_menu[1]->isUnderMouse() && !clicked)
        {
            clicked = true;
            hide_battle_menu(battle_phase);
            battle_phase = 7;
            emit sink_let_go(true);
        }
    }

    if (battle_phase == 11)
    {
        if (battle_start_menu[7]->isUnderMouse() && !clicked)
        {
            clicked = true;
            hide_battle_menu(battle_phase);
            reset_timer();
        }
    }

    //obszar przycisku menu
    if (hud_img[5]->isUnderMouse() && !clicked)
    //if (view->get_x() > 10 && view->get_x() < 150 && view->get_y() > 5 && view->get_y() < 40)
    {
        clicked = true;
        show_menu();
    }

    //obsługa menu
    if (menu_bool)
    {
        clicked = true;
        //if (menu_text[3]->isUnderMouse())
        if (view->get_x() > resolution_x/2 - 200 && view->get_x() < resolution_x/2 +200 && view->get_y() > resolution_y/2 + 45 && view->get_y() < resolution_y/2 + 95)
            QApplication::quit();

        //if (menu_text[4]->isUnderMouse())
        if (view->get_x() > resolution_x/2 - 200 && view->get_x() < resolution_x/2 +200 && view->get_y() > resolution_y/2 + 155 && view->get_y() < resolution_y/2 + 200)
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
    show_menu();
}
