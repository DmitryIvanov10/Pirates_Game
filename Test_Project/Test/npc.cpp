#include "npc.h"
#include <QDebug>

NPC::NPC() : NPC::NPC(0, 0) {}

NPC::NPC(short _start_id, short _finish_id)
{
    //qDebug() <<"Created new NPC!";
    reset();
    /*model = rand() % 2 + 3;
    set_model_parameters();
    health = random_value(max_health);
    crew = random_value(short(max_crew*0.25), short(max_crew*0.75));
    cannons = initial_cannons;
    ammo = random_value(short(max_ammo*0.25), short(max_ammo*0.5));
    maneuverability = max_maneuverability;

    // set cargo
    set_cargo();

    sail_level = 1;
    fraction=rand()%4 + 1;
    active = false;

    set_flag();
    //flag->setPos(get_x() - width/2, get_y()+ height/2);
    //flag->setPos(2000, 1000);
    if (_start_id && _finish_id)
    {
        current_location = _start_id;
        target_location = _finish_id;
    } else
    {
        current_location = rand()%(Voronoi_points::map.size()-1) + 1;
        do
        {
            target_location = rand()%(Voronoi_points::map.size()-1) + 1;
        }
        while (target_location == current_location);
    }

    X = Voronoi_points::map[current_location].get_x();
    Y = Voronoi_points::map[current_location].get_y();


    //qDebug() <<"Current location: " << current_location;
    //qDebug() <<"Target location: " << target_location;
    find_next();*/
}

/*NPC::NPC(double _x, double _y, short _model)
{
    std::srand(time(0));
    fraction=rand()%4 + 1;
    set_flag();
    X=_x;
    Y=_y;
    model=_model;
    active = false;
}*/

NPC::~NPC()
{
    //qDebug() <<"NPC deleted";
    emit delete_npc(this);
    delete flag;
}

int NPC::find_distance(short _id1, short _id2)
{
    // return distance between two voronoi points
    /*return (int)sqrt(
        (Voronoi_points::map[_id2].get_x() - Voronoi_points::map[_id1].get_x()) *
        (Voronoi_points::map[_id2].get_x() - Voronoi_points::map[_id1].get_x()) +
        (Voronoi_points::map[_id2].get_y() - Voronoi_points::map[_id1].get_y()) *
        (Voronoi_points::map[_id2].get_y() - Voronoi_points::map[_id1].get_y())
        );*/
    return find_distance(Voronoi_points::map[_id1].get_x(), Voronoi_points::map[_id1].get_y(), _id2);
}

int NPC::find_distance(double _X, double _Y, short _id)
{
    // returns distance between ship position (X, Y) and voronoi point
    return (int)sqrt(
        (_X - Voronoi_points::map[_id].get_x()) *
        (_X - Voronoi_points::map[_id].get_x()) +
        (_Y - Voronoi_points::map[_id].get_y()) *
        (_Y - Voronoi_points::map[_id].get_y())
        );
}

void NPC::find_next()
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
        //double distance = find_distance(next_id, target_location);

        // check all existing neighbours which left
        while (Voronoi_points::map[current_location].get_neighbour(i) != -1 && i<3)
        {
            //qDebug() <<"Checking id " << Voronoi_points::map[current_location].get_neighbour(i);

            // random choise for locations closer to the target location than current location
            if (find_distance(Voronoi_points::map[current_location].get_neighbour(i), target_location) <
                    find_distance(current_location, target_location))
            {
                //qDebug() <<"This id is not further from target than current location.";
                // check if not a previous location
                if (Voronoi_points::map[current_location].get_neighbour(i) != previous_location)
                {
                    //qDebug() <<"This id is not previous location.";
                    // check if it's a target location
                    if (Voronoi_points::map[current_location].get_neighbour(i) == target_location)
                    {
                        //qDebug() <<"This id is target location.";
                        next_id = Voronoi_points::map[current_location].get_neighbour(i);
                    }
                    else
                    {
                        // coin flip between locations closer to target location than current location
                        /*qDebug() <<"Coin flip between locations " << next_id
                                 <<" and " << Voronoi_points::map[current_location].get_neighbour(i);*/
                        if (rand() % 2)
                        {
                            //qDebug() <<"Decided to choose id " << Voronoi_points::map[current_location].get_neighbour(i);
                            next_id = Voronoi_points::map[current_location].get_neighbour(i);
                        }
                        else
                        {
                            //qDebug() <<"Decided to choose id " << next_id;
                        }
                    }
                }
            }
            /*else
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
                               " is further from target than current location.";
                }
            }*/

            // moving with shortest trace
            /*if (find_distance(Voronoi_points::map[current_location].get_neighbour(i), target_location) < distance)
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
            }*/
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

void NPC::set_direction()
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

/*short NPC::show_fraction()
{
    return fraction;
}*/

void NPC::set_flag()
{
    switch (fraction)
    {
        case 1:
            flag->setPixmap(QPixmap(":/img/Fractions/Flag_British_01.png"));
            break;
        case 2:
            flag->setPixmap(QPixmap(":/img/Fractions/Flag_Spanish_01.png"));
            break;
        case 3:
            flag->setPixmap(QPixmap(":/img/Fractions/Flag_French_01.png"));
            break;
        case 4:
            flag->setPixmap(QPixmap(":/img/Fractions/Flag_Netherlands_01.png"));
            break;
    }
}

void NPC::set_state(bool state)
{
    active = state;
}

bool NPC::get_state()
{
    return active;
}

bool NPC::in_view()
{
    return active;
}

void NPC::move_to_next_location()
{
    if (isUnderMouse())
    {
        showing_info = true;
        emit send_info(this);
    } else
    {
        if (showing_info)
        {
            showing_info = false;
            emit hide_info();
        }
    }
    move();
    setPos(X,Y);
    flag->setPos(X + sprite_width/2, Y);

    // searches next location if close to voronoi point
    if (find_distance(X, Y, next_location) <= 5)
    {
        // check if already at the target location
        if (next_location != target_location)
        {
            //qDebug() <<"Got to the location: " << next_location;
            previous_location = current_location;
            current_location = next_location;
            find_next();
        }
        else
        {
            //qDebug() <<"NPC is at target location: " << next_location;
            //delete this;
            reset();
        }
    }
}

void NPC::reset()
{
    //qDebug() <<"Reseted NPC!";
    current_location = rand()%(Voronoi_points::map.size()-1) + 1;
    do
    {
        target_location = rand()%(Voronoi_points::map.size()-1) + 1;
    }
    while (target_location == current_location);

    X = Voronoi_points::map[current_location].get_x();
    Y = Voronoi_points::map[current_location].get_y();

    model = rand() % 2 + 3;
    set_model_parameters();
    health = random_value(max_health);
    crew = random_value(short(max_crew*0.25), short(max_crew*0.75));
    cannons = initial_cannons;
    ammo = random_value(short(max_ammo*0.25), short(max_ammo*0.5));
    maneuverability = max_maneuverability;

    // set cargo
    set_cargo();

    sail_level = 1;
    fraction=rand()%4 + 1;
    set_name();
    active = false;

    set_flag();

    find_next();
}

/*QString NPC::get_fraction()
{
    switch (fraction)
    {
    case 1:
        return QString("British");
    case 2:
        return QString("Spanish");
    case 3:
        return QString("French");
    case 4:
        return QString("Dutch");
    default:
        return QString("Fraction Error");
    }
}*/
