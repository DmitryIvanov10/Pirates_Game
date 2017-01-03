#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>
#include <QGraphicsScene>

class View : public QGraphicsView
{
    Q_OBJECT

    int res_x;
    int res_y;
public:
    View();
    View(QGraphicsScene *scene);
    View(QGraphicsScene *scene, int _res_x, int _res_y);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:

public slots:
};

#endif // VIEW_H
