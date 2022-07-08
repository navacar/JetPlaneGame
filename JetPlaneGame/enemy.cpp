#include "enemy.h"

const int enemyWidth = 65;
const int enemyHeight = 100;

Enemy::Enemy()
      : enemyImage(":/ABC/images/enemyJet.png")
      , x(500)
      , y(250)
{

}


void Enemy::Draw(QPainter *painter)
{
    painter->drawImage(QRect(x, y - enemyHeight / 2, enemyWidth, enemyHeight), enemyImage);
}
