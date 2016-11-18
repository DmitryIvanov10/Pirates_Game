#include "npc.h"

NPC::NPC()
{
    X=0;
    Y=0;
    model=1;
    std::srand(0);
    fraction=rand()%3;
}

NPC::NPC(double _x, double _y, short _model)
{
    std::srand(0);
    fraction=rand()%3;
    X=_x;
    Y=_y;
    model=_model;
}

void NPC::find_next()
{
    short next_id = 1;
    next_location = next_id;
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
