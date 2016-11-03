//biblioteki
#include <QApplication>
#include <vector>

//pliki
#include "game.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game *game = new Game();

    return a.exec();
}
