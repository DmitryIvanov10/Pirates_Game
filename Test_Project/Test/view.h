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
public:
    View();
    View(QGraphicsScene *scene);

    void mousePressEvent(QMouseEvent *event);

signals:

public slots:
};

#endif // VIEW_H
