#include <QRandomGenerator>
#include "meteorite.h"

const int meteoriteSize = 100;

Meteorite::Meteorite()
          : meteoriteImage(QImage(":/ABC/images/meteorite.png"))
          , y(-50)
{
    x = QRandomGenerator::global()->bounded(200, 850);
}


void Meteorite::Draw(QPainter *painter)
{
    painter->drawImage(QRect(x, y - meteoriteSize / 2, meteoriteSize, meteoriteSize), meteoriteImage);
}


void Meteorite::Move()
{
    y += 10;
    x -= 5;
    meteoriteRect = QRect(x + 20, y - meteoriteSize / 2 + 20, meteoriteSize - 42, meteoriteSize - 42);
}


QRect Meteorite::GetMeteoriteRect()
{
    return meteoriteRect;
}


int Meteorite::GetMeteoriteBotoomY()
{
    return y + meteoriteSize - 60;
}
