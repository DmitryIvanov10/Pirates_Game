#include "view.h"

View::View() :QGraphicsView::QGraphicsView()
{
    setMouseTracking(true);
}

View::View(QGraphicsScene *scene) : QGraphicsView::QGraphicsView(scene)
{
    setMouseTracking(true);
}

View::View(QGraphicsScene *scene, int _res_x, int _res_y) : QGraphicsView::QGraphicsView(scene)
{
    setMouseTracking(true);
    res_x = _res_x;
    res_y = _res_y;
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << event->x() << " " << event->y();
}

void View::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "wciskam " << event->x() << " " << event->y();
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "puszczam";
}
