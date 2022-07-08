#include "earth.h"

const int earthWidth = 450;
const int earthHeight = 120;

Earth::Earth()
{
    int x = 0;
    int y = 480;
    EarthStructure structure;
    structure.earthImage = QImage(":/ABC/images/earth.jpg");
    for (int i = 0; i < 3; i++)
    {

        structure.x = x;
        structure.y = y;
        x += earthWidth;

        earthVector.append(structure);
    }
}


void Earth::Draw(QPainter *painter)
{
    for (int i = 0; i < 3; i++)
    {
        painter->drawImage(QRect(earthVector[i].x, earthVector[i].y, earthWidth , earthHeight), earthVector[i].earthImage);
    }
}


void Earth::Move()
{
    for (int i = 0; i < 3; i++)
    {
       earthVector[i].x -= 10;
    }

    ReplacePlate();
}


void Earth::ReplacePlate()
{
    if (earthVector[1].x <= 0)
    {
        earthVector.removeAt(0);
        EarthStructure structure = earthVector[1];
        structure.x += earthWidth;
        earthVector.append(structure);
    }
}


int Earth::GetY()
{
    return 492;
}

