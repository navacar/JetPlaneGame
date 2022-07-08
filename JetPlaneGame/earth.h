#ifndef EARTH_H
#define EARTH_H

#include <QPainter>
#include <QImage>

class Earth
{

private:
    struct EarthStructure
    {
        QImage earthImage;
        int x;
        int y;
    };

    void ReplacePlate();


public:
    Earth();
    void Move();
    void Draw(QPainter *painter);
    int GetY();

private:
    QVector<EarthStructure> earthVector;

};

#endif // EARTH_H
