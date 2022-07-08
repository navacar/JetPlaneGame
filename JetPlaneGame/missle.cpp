#include "missle.h"

Missle::Missle(int x, int y)
       : missleImage(":/ABC/images/friendlyMissle.png")
       , missleWidth(50)
       , missleHeight(20)
{
    this->x = x;
    this->y = y;
}


int Missle::GetX()
{
    return x;
}


int Missle::GetRightBorder()
{
    return x + missleWidth;
}


int Missle::GetBottomBorder()
{
    return y + missleHeight;
}


void Missle::Move()
{
    y++;
    x += 17;
    missleRect = QRect(x, y - missleHeight / 2, missleWidth, missleHeight);
}


void Missle::Draw(QPainter *painter)
{
    painter->drawImage(QRect(x, y - missleHeight / 2, missleWidth, missleHeight), missleImage);
}


QRect Missle::GetMissleRect()
{
    return missleRect;
}
