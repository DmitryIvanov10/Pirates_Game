#include "npc.h"

NPC::NPC()
{
    std::srand(0);
    fraction=rand()%3;
}

void NPC::find_next()
{
    //to do
}

short NPC::show_fraction()
{
    return fraction;
}
