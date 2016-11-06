#ifndef PLAYER_H
#define PLAYER_H

//biblioteki
#include <QObject>
#include <QGraphicsRectItem> //dziedziczenie itemu z grafik
#include <QKeyEvent> //obługa klawiszy
#include <QDebug> //obsługa konsoli Qt

class Player: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    void keyPressEvent(QKeyEvent * event);

public slots:
    void move();

signals:


};

#endif // PLAYER_H
