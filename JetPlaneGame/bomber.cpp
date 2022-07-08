#include <QRandomGenerator>
#include "bomber.h"

const int bomberSize = 160;

Bomber::Bomber()
       : bomberImage(QImage(":/ABC/images/enemyBomber.png"))
       , x(950)
{
    int verticalPosition = QRandomGenerator::global()->bounded(2);

    if (verticalPosition == 0)
    {
        y = 80;
        movementSpeed = 20;
    }
    else
    {
        y = 240;
        movementSpeed = 15;
    }
}


void Bomber::Draw(QPainter *painter)
{
    painter->drawImage(QRect(x, y - bomberSize / 2, bomberSize, bomberSize), bomberImage);
}


void Bomber::Move()
{
    x -= movementSpeed;
    firstBomberRect = QRect(x + 10, y - 10, 80, 20);
    secondBomberRect = QRect(x + 80, y - 45, 20, 90);
}


bool Bomber::CheckCollision(QRect itemRect)
{
    bool isCrossed = false;

    if (firstBomberRect.intersects(itemRect))
    {
        isCrossed = true;
    }
    else if (secondBomberRect.intersects(itemRect))
    {
        isCrossed = true;
    }

    return isCrossed;
}


int Bomber::GetRightX()
{
    return x + bomberSize;
}
