#ifndef ENEMYMISSLE_H
#define ENEMYMISSLE_H

#include "missle.h"

class EnemyMissle : public Missle
{
public:
    EnemyMissle(int x, int y);

    void Move();
    int GetRightX();
};

#endif // ENEMYMISSLE_H
