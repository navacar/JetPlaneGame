#include <QRandomGenerator>
#include "enemyjet.h"

const int jetSize = 75;
const int movementSpeed = 20;
const int defaultDelay = 20;
const int defaultCooldown = 30;

EnemyJet::EnemyJet()
         : jetImage(":/ABC/images/enemyJet.png")
         , x(950) // 950
         , gunCoolDown(1)
         , isGunFired(false)
         , counterToChangeDirection(defaultDelay)
         , direction(0)
{
    int verticalPosition = QRandomGenerator::global()->bounded(3);

    if (verticalPosition == 0)
    {
        y = 280;
    }
    else if (verticalPosition == 1)
    {
        y = 220;
    }
    else
    {
        y = 160;
    }
}


void EnemyJet::Draw(QPainter *painter)
{
    painter->drawImage(QRect(x, y - jetSize / 2, jetSize, jetSize), jetImage);
}


void EnemyJet::SetIsGunFired(bool isGunFired)
{
    this->isGunFired = isGunFired;
}


void EnemyJet::Move()
{
    gunCoolDown--;

    if (isGunFired)
    {
        gunCoolDown = defaultCooldown;
        isGunFired = false;
    }

    x -= movementSpeed;
    counterToChangeDirection--;

    if (y + jetSize / 2 >= 320)
    {
        direction = 0;
        y--;
    }
    else if (y - jetSize / 2 <= 160)
    {
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
            counterToChangeDirection = defaultDelay;
            y++;
        }
        else
        {
            counterToChangeDirection = defaultDelay;
            y--;
        }
    }

    jetRect = QRect(x + 30, y - jetSize / 2 + 5, jetSize - 40, jetSize - 10);
}


QRect EnemyJet::GetJetRect()
{
    return jetRect;
}


int EnemyJet::GetXForMissle()
{
    return x;
}


int EnemyJet::GetYForMissle()
{
    return y;
}


int EnemyJet::GetGunCoolDown()
{
    return gunCoolDown;
}


int EnemyJet::GetRightX()
{
    return x + jetSize;
}
