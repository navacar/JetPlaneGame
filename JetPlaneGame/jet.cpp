#include "jet.h"

const int jetSize = 75;
const int maxMovementSpeed = 10;

Jet::Jet()
    : jetImage(QImage(":/ABC/images/playerJet.png"))
    , x(32)
    , y(240)
    , movementSpeed(0)
    , speedSymbol(false)
{
}


void Jet::Move(int newY)
{
    if (newY <= jetSize / 2)
    {
        newY = jetSize / 2;
    }


    if (newY > y)
    {
        if (!speedSymbol)
        {
            movementSpeed = 0;
            speedSymbol = true;
        }

        if (movementSpeed != maxMovementSpeed)
        {
            movementSpeed++;
        }

        int newMovementSpeed = newY - y;

        if (movementSpeed > newMovementSpeed)
        {
            movementSpeed = newMovementSpeed;
        }
    }
    else if (newY < y)
    {
        if (speedSymbol)
        {
            movementSpeed = 0;
            speedSymbol = false;
        }

        if (movementSpeed != -1 * maxMovementSpeed)
        {
            movementSpeed--;
        }

        int newMovementSpeed = y - newY;

        if (movementSpeed > newMovementSpeed)
        {
            movementSpeed = newMovementSpeed;
        }
    }
    else
    {
        movementSpeed = 0;
    }

    y += movementSpeed;
    jetRect = QRect(x + 10, y - jetSize / 2 + 4, jetSize - 40, jetSize - 10);
}


int Jet::GetYForMissle()
{
    return y;
}


int Jet::GetXForMissle()
{
    return x + jetSize - 15;
}


int Jet::GetBottomY()
{
    return y + jetSize / 2 + 7; // 7 для более корректной колизиии
}


void Jet::Draw(QPainter *painter)
{
    painter->drawImage(QRect(x, y - jetSize / 2, jetSize, jetSize), jetImage);
}


QRect Jet::GetJetRect()
{
    return jetRect;
}
