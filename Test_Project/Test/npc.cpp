#include "npc.h"

NPC::NPC()
{
    std::srand(0);
    fraction=rand()%3;
}

void NPC::find_next()
{
    short next_id = 1;
    next_location = next_id;
}

void NPC::set_direction()
{
    double _x = 50;
    double _y = 50;
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
