#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>

#include "Player.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    

    // create a scene
    QGraphicsScene * scene = new QGraphicsScene();

    // create an item to put into the scene
    Player * rect = new Player();
    rect->setRect(0,0,100,100);

    // add the item to the theme
    scene->addItem(rect);

    // add a view
    QGraphicsView * view = new QGraphicsView(scene);

    //make item focus
    rect->setFlag(QGraphicsItem::ItemIsFocusable);
    rect->setFocus();

    view->show();
    return a.exec();
}
