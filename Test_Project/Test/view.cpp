#include "view.h"

View::View() :QGraphicsView::QGraphicsView()
{
    setMouseTracking(true);
}

View::View(QGraphicsScene *scene) : QGraphicsView::QGraphicsView(scene)
{
    setMouseTracking(true);
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << event->x() << " " << event->y();
    X = event->x();
    Y = event->y();
    emit mouse_moved();
}

void View::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << "wciskam " << event->x() << " " << event->y();
    switch (event->buttons())
    {
        case Qt::LeftButton:
            emit mouse_left_pressed();
        case Qt::RightButton:
            emit mouse_right_pressed();
    }

    //emit mouse_pressed();
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    //qDebug() << "puszczam";
    emit mouse_released();
}

int View::get_x()
{
    return X;
}

int View::get_y()
{
    return Y;
}
