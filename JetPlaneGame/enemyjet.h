#ifndef ENEMYJET_H
#define ENEMYJET_H

#include <QImage>
#include <QPainter>
#include <QRect>

class EnemyJet
{
public:
    EnemyJet();

    void Move();
    void Draw(QPainter *painter);

    QRect GetJetRect();

    int GetXForMissle();
    int GetYForMissle();

    int GetRightX();

    int GetGunCoolDown();
    void SetIsGunFired(bool isGunFired);

private:
    QRect jetRect;
    QImage jetImage;

    int x;
    int y;

    int gunCoolDown;
    bool isGunFired;

    int counterToChangeDirection;
    int direction;

};

#endif // ENEMYJET_H
