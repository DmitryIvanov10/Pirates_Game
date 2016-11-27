#include "npc.h"
#include <QDebug>

NPC::NPC()
{
    std::srand(time(0));
    model=1;
    sail_level = 1;
    fraction=rand()%3;
    current_location = rand()%(Game::map.size()-1) + 1;
    target_location = current_location;
    X = Game::map[current_location].get_x();
    Y = Game::map[current_location].get_y();
    while (target_location == current_location)
    {
        target_location = rand()%(Game::map.size()-1) + 1;
    }
    qDebug() <<"Current location: " << current_location;
    qDebug() <<"Target location: " << target_location;
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

NPC::~NPC()
{
    qDebug() <<"NPC deleted";
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

int NPC::find_distance(double _X, double _Y, short _id)
{
    return (int)sqrt(
        (_X - Game::map[_id].get_x()) *
        (_X - Game::map[_id].get_x()) +
        (_Y - Game::map[_id].get_y()) *
        (_Y - Game::map[_id].get_y())
        );
}

void NPC::find_next()
{
    short i = 0;
    if (Game::map[current_location].get_neighbour(i) == previous_location &&
        Game::map[current_location].get_neighbour(i+1) != -1)
    {
        qDebug() <<"Location " << Game::map[current_location].get_neighbour(i) <<
                   " is previous location and doesn't fit.";
        ++i;
    }
    while (find_distance(Game::map[current_location].get_neighbour(i), target_location) >
           find_distance(current_location, target_location) &&
           Game::map[current_location].get_neighbour(i+1) != -1 && i<3)
    {
        if (Game::map[current_location].get_neighbour(i) == previous_location)
        {
            qDebug() <<"Location " << Game::map[current_location].get_neighbour(i) <<
                       " is previous location.";
        }
        else
        {
            qDebug() <<"Location " << Game::map[current_location].get_neighbour(i) <<
                       " is further from target than current location.";
        }
        ++i;
    }
    short next_id = Game::map[current_location].get_neighbour(i);
    qDebug() <<"First choice is location " << next_id;
    ++i;
    if (next_id != target_location)
    {
        //for shortest distance method only
        double distance = find_distance(next_id, target_location);

        while (Game::map[current_location].get_neighbour(i) != -1 && i<3)
        {
            qDebug() <<"Checking id " << Game::map[current_location].get_neighbour(i);

            //Randomny wybór dla pónktów o podobnej odległości od target_location
            if (find_distance(Game::map[current_location].get_neighbour(i), target_location) <
                    find_distance(current_location, target_location))
            {
                qDebug() <<"This id is not further from target than current location.";
                if (Game::map[current_location].get_neighbour(i) != previous_location)
                {
                    qDebug() <<"This id is not previous location.";
                    if (Game::map[current_location].get_neighbour(i) == target_location)
                    {
                        qDebug() <<"This id is target location.";
                        next_id = Game::map[current_location].get_neighbour(i);
                    }
                    else
                    {
                        qDebug() <<"Coin flip between locations " << next_id
                                 <<" and " << Game::map[current_location].get_neighbour(i);
                        if (rand() % 2)
                        {
                            qDebug() <<"Decided to choose id " << Game::map[current_location].get_neighbour(i);
                            next_id = Game::map[current_location].get_neighbour(i);
                        }
                        else
                        {
                            qDebug() <<"Decided to choose id " << next_id;
                        }
                    }
                }
            }
            else
            {
                if (Game::map[current_location].get_neighbour(i) == previous_location)
                {
                    qDebug() <<"Location " << Game::map[current_location].get_neighbour(i) <<
                               " is previous location.";
                }
                else
                {
                    qDebug() <<"Location " << Game::map[current_location].get_neighbour(i) <<
                               " is further from target than current location.";
                }
            }

            //Poruszanie się najkrótszą drogą
            /*if (find_distance(Game::map[current_location].get_neighbour(i), target_location) < distance)
            {
                qDebug() <<"Location " << Game::map[current_location].get_neighbour(i) <<
                           " is closer than location " << next_id;
                distance = find_distance(Game::map[current_location].get_neighbour(i), target_location);
                next_id = Game::map[current_location].get_neighbour(i);
            }
            else
            {
                if (Game::map[current_location].get_neighbour(i) == previous_location)
                {
                    qDebug() <<"Location " << Game::map[current_location].get_neighbour(i) <<
                               " is previous location.";
                }
                else
                {
                    qDebug() <<"Location " << Game::map[current_location].get_neighbour(i) <<
                           " is further than location " << next_id;
                }
            }*/
            ++i;
        }
    }
    else
    {
        qDebug() <<"This id is target location.";
    }
    next_location = next_id;
    qDebug() <<"Next location: " << next_location;
    set_angle(atan2(Y - Game::map[next_location].get_y(), Game::map[next_location].get_x() - X) * 180 / M_PI - 90);
}

void NPC::set_direction()
{
    /*// get x and y coordinates of the location (next voronoi point)
    double _x = Game().get_x(next_location);
    double _y = Game().get_y(next_location);

    // set the angle to the location (next voronoi point)
    double _angle = atan2(get_y()-_y, _x - get_x()) * 180 / M_PI - 90;
    set_angle(_angle);*/
    set_angle(atan2(get_y()-Game().get_y(next_location),
              Game().get_x(next_location) - get_x()) * 180 / M_PI - 90);
}

short NPC::show_fraction()
{
    return fraction;
}

void NPC::move_to_next_location()
{
    move();
    setPos(X,Y);
    if (find_distance(X, Y, next_location) <= 5)
    {
        if (next_location != target_location)
        {
            qDebug() <<"Got to the location: " << next_location;
            //qDebug() <<"NPC is at point X: " << X << ", Y: " << Y;
            previous_location = current_location;
            current_location = next_location;
            find_next();
        }
        else
        {
            qDebug() <<"NPC is at target location: " << next_location;
            delete this;
        }
    }
}
