//biblioteki
#include <QApplication>
#include <vector>
//#include <QtPlugin>
//Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin);

//pliki
#include "game.h"

std::vector<Voronoi_point> Voronoi_points::map;
short Wind::angle;
short Wind::strength;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game *game = new Game();

    return a.exec();
}
