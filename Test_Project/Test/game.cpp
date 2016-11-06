#include "game.h"

Game::Game(QObject *parent) : QObject(parent)
{  
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

    connect (timer, SIGNAL(timeout()), rect, SLOT(move()));
    timer->start(17);

    view->show();
}

Game::Game(std::string a)
{
    std::ifstream load(a.c_str());
    if(load)
    {
        //to do
    }
}
