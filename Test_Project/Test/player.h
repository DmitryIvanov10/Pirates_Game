#ifndef PLAYER_H
#define PLAYER_H

//biblioteki
#include <QGraphicsRectItem> //dziedziczenie itemu z grafik
#include <QKeyEvent> //obługa klawiszy
#include <QDebug> //obsługa konsoli Qt

class Player: public QGraphicsRectItem
{
public:
    void keyPressEvent(QKeyEvent * event);
};

#endif // PLAYER_H
