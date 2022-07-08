#include "enemymissle.h"

EnemyMissle::EnemyMissle(int x, int y)
            : Missle(x, y)
{
    this->x = x;
    this->y = y;
    this->missleImage = QImage(":/ABC/images/enemyMissle.png");
}


void EnemyMissle::Move()
{
    this->y++;
    this->x -= 25;
    this->missleRect = QRect(x, y - missleHeight / 2, missleWidth, missleHeight);
}


int EnemyMissle::GetRightX()
{
    return x + missleWidth;
}
