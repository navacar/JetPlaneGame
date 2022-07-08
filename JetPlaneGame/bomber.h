#ifndef BOMBER_H
#define BOMBER_H

#include <QImage>
#include <QPainter>
#include <QRect>

class Bomber
{
public:
    Bomber();

    void Move();
    void Draw(QPainter *painter);
    bool CheckCollision(QRect itemRect);

    int GetRightX();

private:
    QImage bomberImage;
    QRect firstBomberRect;
    QRect secondBomberRect;

    int x;
    int y;

    int movementSpeed;

};

#endif // BOMBER_H
