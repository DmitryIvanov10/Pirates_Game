#include "view.h"

View::View() :QGraphicsView::QGraphicsView()
{
    //setMouseTracking(true);
}

View::View(QGraphicsScene *scene) : QGraphicsView::QGraphicsView(scene)
{
    //setMouseTracking(true);
}

void View::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "jej :D";
}
