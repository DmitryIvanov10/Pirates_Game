#ifndef WIND_H
#define WIND_H

#include <QObject>

class Wind : public QObject
{
    Q_OBJECT

    short angle; //kąt wiatru w stopniach
    short strenght; //siła wiatru, wartości pomiędzy 0 a 99

public:
    explicit Wind(QObject *parent = 0);
    void change_all(); //zmiana kątu i siły o losowy czynnik
    void change_angle(); //zmiana kątu o losowy czynnik
    void change_strenght(); //zmiana siły o losowy czynnik

signals:

public slots:
};

#endif // WIND_H
