#ifndef BIRD_H
#define BIRD_H

#include <QImage>
#include <QPainter>
#include <QRect>

class Bird
{
public:
    Bird();

    void Move();
    void Draw(QPainter *painter);

    int GetRightX();

    QRect GetBirdRect();

private:
    QImage birdImage;
    QRect birdRect;

    int x;
    int y;

    int direction;

    int counterToChangeDirection;
};

#endif // BIRD_H
