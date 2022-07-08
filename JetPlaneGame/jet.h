#ifndef JET_H
#define JET_H

#include <QImage>
#include <QPainter>
#include <QRect>


class Jet
{

public:
    Jet();

    int GetBottomY();
    int GetYForMissle();
    int GetXForMissle();

    void Draw(QPainter *painter);
    void Move(int newY);

    QRect GetJetRect();

private:
    QImage jetImage;
    QRect jetRect;

    int x;
    int y;
    int movementSpeed;

    bool speedSymbol;

};

#endif // JET_H
