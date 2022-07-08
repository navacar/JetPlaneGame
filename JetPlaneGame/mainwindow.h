#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QTimer>
#include "earth.h"
#include "jet.h"
#include "missle.h"
#include "bomber.h"
#include "bird.h"
#include "enemyjet.h"
#include "enemymissle.h"
#include "meteorite.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    void GameOverFunction();
    void WinFunction();

    void EnemySpawner();

    void Collision();
    void MeteoriteCollision();
    void Hit();

    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

    void DeleteMissle(int index);
    void DeleteEnemyMissle(int index);
    void DeleteBird(int index);
    void DeleteBomber(int index);
    void DeleteEnemyJet(int index);
    void DeleteMeteorite();


private slots:
   void Update();

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Earth *newEarth;
    Jet *newJet;

    Meteorite *newMeteorite;

    QVector<Bomber *> bombersVector;
    QVector<Bird *> birdsVector;
    QVector<EnemyJet *> enemyJetsVector;

    QVector<Missle *> friendlyMissles;
    QVector<EnemyMissle *> enemyMissles;

    int enemySpawnDelay;

    int score;
    int fireSpeed;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
