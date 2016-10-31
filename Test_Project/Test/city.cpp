#include "city.h"

City::City(short a)
{
    voronoi=a;
    fraction=1;
    id=1;
}

City::City(short a, short b)
{
    voronoi=a;
    fraction=b;
    id=1;
}

City::City(short a, short b, short c)
{
    voronoi=a;
    fraction=b;
    id=c;
}
