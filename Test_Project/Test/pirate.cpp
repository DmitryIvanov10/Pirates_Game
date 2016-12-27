#include "pirate.h"
#include <QDebug>

Pirate::Pirate()
{
    model=1;
    sail_level = 1;
    fight_active = true;
    active = false;

    current_location = rand()%(Voronoi_points::map.size()-1) + 1;
    X = Voronoi_points::map[current_location].get_x();
    Y = Voronoi_points::map[current_location].get_y();

    find_next();
}

Pirate::Pirate(short _start_id)
{
    model=1;
    sail_level = 1;
    fight_active = true;
    active = false;

    current_location = _start_id;
    X = Voronoi_points::map[current_location].get_x();
    Y = Voronoi_points::map[current_location].get_y();

    find_next();
}

Pirate::~Pirate()
{
    //qDebug() << "Pirate deleted";
}

void Pirate::find_next()
{
    // check if first neighbour is a previous position
    // if yes and there are more neighbours - ship first neighbour
    short i = 0;
    if (Voronoi_points::map[current_location].get_neighbour(i) == previous_location &&
        Voronoi_points::map[current_location].get_neighbour(i+1) != -1)
    {
        /*qDebug() <<"Location " << Voronoi_points::map[current_location].get_neighbour(i) <<
                   " is previous location and doesn't fit.";*/
        ++i;
    }
    // skip all neighbours which are further from target location and are not the last neighbours
    while (find_distance(Voronoi_points::map[current_location].get_neighbour(i), target_location) >
           find_distance(current_location, target_location) &&
           Voronoi_points::map[current_location].get_neighbour(i+1) != -1 && i<3)
    {
        // for debug purposes only
        /*if (Voronoi_points::map[current_location].get_neighbour(i) == previous_location)
        {
            qDebug() <<"Location " << Voronoi_points::map[current_location].get_neighbour(i) <<
                       " is previous location.";
        }
        else
        {
            qDebug() <<"Location " << Voronoi_points::map[current_location].get_neighbour(i) <<
                       " is further from target than current location.";
        }*/
        ++i;
    }
    // first appropriate choise for next location
    short next_id = Voronoi_points::map[current_location].get_neighbour(i);
    //qDebug() <<"First choice is location " << next_id;
    ++i;
    // check if choise is a target location
    if (next_id != target_location)
    {
        //for shortest distance method only
        double distance = find_distance(next_id, target_location);

        // check all existing neighbours which left
        while (Voronoi_points::map[current_location].get_neighbour(i) != -1 && i<3)
        {
            //qDebug() <<"Checking id " << Voronoi_points::map[current_location].get_neighbour(i);

            // moving with shortest trace
            if (find_distance(Voronoi_points::map[current_location].get_neighbour(i), target_location) < distance)
            {
                qDebug() <<"Location " << Voronoi_points::map[current_location].get_neighbour(i) <<
                           " is closer than location " << next_id;
                distance = find_distance(Voronoi_points::map[current_location].get_neighbour(i), target_location);
                next_id = Voronoi_points::map[current_location].get_neighbour(i);
            }
            else
            {
                // for debug purposes only
                if (Voronoi_points::map[current_location].get_neighbour(i) == previous_location)
                {
                    qDebug() <<"Location " << Voronoi_points::map[current_location].get_neighbour(i) <<
                               " is previous location.";
                }
                else
                {
                    qDebug() <<"Location " << Voronoi_points::map[current_location].get_neighbour(i) <<
                           " is further than location " << next_id;
                }
            }
            ++i;
        }
    }
    /*else
    {
        qDebug() <<"This id is target location.";
    }*/

    // set next location and angle to it
    next_location = next_id;
    //qDebug() <<"Next location: " << next_location;
    set_angle(atan2(Y - Voronoi_points::map[next_location].get_y(),
                    Voronoi_points::map[next_location].get_x() - X) * 180 / M_PI - 90);
}

int Pirate::find_distance(short _id1, short _id2)
{
    // return distance between two voronoi points
    return (int)sqrt(
        (Voronoi_points::map[_id2].get_x() - Voronoi_points::map[_id1].get_x()) *
        (Voronoi_points::map[_id2].get_x() - Voronoi_points::map[_id1].get_x()) +
        (Voronoi_points::map[_id2].get_y() - Voronoi_points::map[_id1].get_y()) *
        (Voronoi_points::map[_id2].get_y() - Voronoi_points::map[_id1].get_y())
        );
}

int Pirate::find_distance(double _X, double _Y, short _id)
{
    // returns distance between ship position (X, Y) and voronoi point
    return (int)sqrt(
        (_X - Voronoi_points::map[_id].get_x()) *
        (_X - Voronoi_points::map[_id].get_x()) +
        (_Y - Voronoi_points::map[_id].get_y()) *
        (_Y - Voronoi_points::map[_id].get_y())
        );
}


void Pirate::set_direction()
{
    /*// get x and y coordinates of the location (next voronoi point)
    double _x = Game().get_x(next_location);
    double _y = Game().get_y(next_location);

    // set the angle to the location (next voronoi point)
    double _angle = atan2(get_y()-_y, _x - get_x()) * 180 / M_PI - 90;
    set_angle(_angle);*/
    // set the angle to the location (next voronoi point)
    set_angle(atan2(get_y() - Voronoi_points::map[next_location].get_y(),
                    Voronoi_points::map[next_location].get_x() - get_x()) * 180 / M_PI - 90);
}

void Pirate::set_state(bool state)
{
    active = state;
}

bool Pirate::in_view()
{
    return active;
}
