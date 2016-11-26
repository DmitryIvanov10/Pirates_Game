//biblioteki
#include <QApplication>
#include <vector>

//pliki
#include "game.h"

std::vector<Voronoi_point> Game::map;
short Wind::angle;
short Wind::strength;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game *game = new Game();

    return a.exec();
}
