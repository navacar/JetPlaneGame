#ifndef METEORITE_H
#define METEORITE_H


#include <QImage>
#include <QPainter>
#include <QRect>

class Meteorite
{
public:
    Meteorite();

    void Draw(QPainter *painter);
    void Move();

    QRect GetMeteoriteRect();
    int GetMeteoriteBotoomY();


private:
    QImage meteoriteImage;
    QRect meteoriteRect;

    int x;
    int y;
};

#endif // METEORITE_H
