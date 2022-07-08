#include <QRandomGenerator>
#include "bird.h"

const int birdSize = 50;
const int defaultDelay = 15;
const int movementSpeed = 7;

Bird::Bird()
     : birdImage(QImage(":/ABC/images/enemyBird.png"))
     , x(950)
     , y(450)
     , direction(0)
     , counterToChangeDirection(defaultDelay)
{
}


void Bird::Draw(QPainter *painter)
{
    painter->drawImage(QRect(x, y - birdSize / 2, birdSize, birdSize), birdImage);
}


void Bird::Move()
{
    x -= movementSpeed;
    counterToChangeDirection--;

    if (y + birdSize / 2 >= 480)
    {
        counterToChangeDirection = defaultDelay;
        direction = 0;
        y--;
    }
    else if (y - birdSize / 2 <= 320)
    {
        counterToChangeDirection = defaultDelay;
        direction = 1;
        y++;
    }
    else
    {
        if(counterToChangeDirection == 0)
        {
            counterToChangeDirection = defaultDelay;
            direction = QRandomGenerator::global()->bounded(2);
        }

        if (direction == 1)
        {
            y++;
        }
        else
        {
            y--;
        }
    }

    birdRect = QRect(x + 13, y - birdSize / 2, birdSize - 30, birdSize);
}


int Bird::GetRightX()
{
    return x + birdSize;
}


QRect Bird::GetBirdRect()
{
    return birdRect;
}
