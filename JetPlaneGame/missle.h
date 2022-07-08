#ifndef MISSLE_H
#define MISSLE_H

#include <QImage>
#include <QPainter>
#include <QRect>


class Missle
{
public:
    Missle(int x, int y);

    int GetX();

    int GetRightBorder();
    int GetBottomBorder();

    QRect GetMissleRect();

    void Move();
    void Draw(QPainter *painter);

protected:
    QImage missleImage;
    QRect missleRect;

    int y;
    int x;
    int missleWidth;
    int missleHeight;
};

#endif // MISSLE_H
