#ifndef ISLAND_H
#define ISLAND_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Island : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    short id; //nipowtarzalne id wyspy
    short texture_number; //rodzaj wyświetlanej tekstury wyspy

    double x; //położenie x
    double y; //położenie y

public:
    explicit Island(QObject *parent = 0);
    Island(double _x, double _y, short _texture_number, short _id); //pełny kostruktor argumentowy

    //funkcje dostępu
    double get_x();
    double get_y();
    void set_texture();

signals:

public slots:
};

#endif // ISLAND_H
