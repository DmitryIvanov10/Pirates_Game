#ifndef GAME_H
#define GAME_H

//biblioteki
#include <QObject> //potrzebne do slotów i sygnałów
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <fstream>
#include <QTimer> //potrzebny do Qtimer'a

//pliki
#include "Player.h"

class Game : public QObject
{
    Q_OBJECT

    QTimer *timer = new QTimer();

public:
    //konstruktory
    explicit Game(QObject *parent = 0); //nowa gra
    Game(std::string a); //wczytanie gry o nazwie a

signals:

public slots:
};

#endif // GAME_H
