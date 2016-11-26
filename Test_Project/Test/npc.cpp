#include "npc.h"
#include <QDebug>

NPC::NPC()
{
    std::srand(time(0));
    model=1;
    fraction=rand()%3;
    current_location = rand()%(Game::map.size());
    X = Game::map[current_location].get_x();
    Y = Game::map[current_location].get_y();
    target_location = rand()%(Game::map.size());
    qDebug() <<"Current location: " << current_location << "NPC_X: " << X <<", NPC_Y: " << Y;
    qDebug() <<"Target location: " << current_location << "NPC_X: " << X <<", NPC_Y: " << Y;
}

NPC::NPC(double _x, double _y, short _model)
{
    std::srand(time(0));
    fraction=rand()%3;
    X=_x;
    Y=_y;
    model=_model;
}

void NPC::find_next()
{
    short next_id = Game::map[current_location].get_neighbour(0);
    double distance = find_distance(next_id, target_location);
    short i = 1;
    while (Game::map[current_location].get_neighbour(i) != -1 && i<3)
    {
        if (find_distance(Game::map[current_location].get_neighbour(i), target_location) < distance)
        {
            distance = find_distance(Game::map[current_location].get_neighbour(i), target_location);
            next_id = Game::map[current_location].get_neighbour(i);
        }
    }
    next_location = next_id;
    qDebug() <<"Next location: " << next_location;
}

void NPC::set_direction()
{
    // get x and y coordinates of the location (next voronoi point)
    double _x = Game().get_x(next_location);
    double _y = Game().get_y(next_location);

    // set the angle to the location (next voronoi point)
    double _angle = atan2(get_y()-_y, _x - get_x()) * 180 / M_PI - 90;
    set_angle(_angle);
}

short NPC::show_fraction()
{
    return fraction;
}

void NPC::move_to_next_location()
{
    // next_

}
