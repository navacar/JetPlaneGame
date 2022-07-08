#ifndef ENEMY_H
#define ENEMY_H

#include <QImage>
#include <QPainter>

class Enemy
{
public:
    Enemy();

    void Draw(QPainter *painter);
    void Move(int newY);

    int GetTopBorder();
//    int GetBottomBorder();
    int GetLeftBorder();

protected:
    QImage enemyImage;


    int movementSpeed;
    int x;
    int y;


};

#endif // ENEMY_H
