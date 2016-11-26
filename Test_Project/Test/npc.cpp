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
    //qDebug() << rand()%(Game::map.size());
    //qDebug() << rand()%(Game::map.size());
    qDebug() <<"Current location: " << current_location << ". X: " <<
               Game::map[current_location].get_x() <<", Y: " <<
               Game::map[current_location].get_y();
    qDebug() <<"Target location: " << target_location << ". X: " <<
               Game::map[target_location].get_x() <<", Y: " <<
               Game::map[target_location].get_y();
    find_next();
}

NPC::NPC(double _x, double _y, short _model)
{
    std::srand(time(0));
    fraction=rand()%3;
    X=_x;
    Y=_y;
    model=_model;
}

int NPC::find_distance(short _id1, short _id2)
{
    return (int)sqrt(
        (Game::map[_id2].get_x() - Game::map[_id1].get_x()) *
        (Game::map[_id2].get_x() - Game::map[_id1].get_x()) +
        (Game::map[_id2].get_y() - Game::map[_id1].get_y()) *
        (Game::map[_id2].get_y() - Game::map[_id1].get_y())
        );
}

void NPC::find_next()
{
    qDebug() << "Looking for next location: ...";
    short next_id = Game::map[current_location].get_neighbour(0);
    qDebug() << "First neighbour has id: " << next_id;
    double distance = find_distance(next_id, target_location);
    qDebug() << "Distance is: " << distance;
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
