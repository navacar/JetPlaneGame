#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>
#include <QRandomGenerator>

#include "mainwindow.h"
#include "ui_mainwindow.h"


const int defaultFireSpeed = 20;
const int defaultWinCondition = 400;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , enemySpawnDelay(0)
    , score(0)
    , fireSpeed(defaultFireSpeed)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setFixedSize(QWidget::size());

    newEarth = new Earth();
    newJet = new Jet();

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    timer->start(40);
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && fireSpeed == defaultFireSpeed)
    {
        friendlyMissles.append(new Missle(newJet->GetXForMissle(), newJet->GetYForMissle()));
        fireSpeed = 0;
    }

    repaint();
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    newEarth->Draw(&painter);
    newJet->Draw(&painter);

    if (newMeteorite)
    {
        newMeteorite->Draw(&painter);
    }

    for (int i = 0; i < bombersVector.size(); i++)
    {
        if (bombersVector[i] != nullptr)
        {
            bombersVector[i]->Draw(&painter);
        }
    }

    for (int i = 0; i < birdsVector.size(); i++)
    {
        if (birdsVector[i] != nullptr)
        {
            birdsVector[i]->Draw(&painter);
        }
    }

    for (int i = 0; i < enemyJetsVector.size(); i++)
    {
        if (enemyJetsVector[i] != nullptr)
        {
            enemyJetsVector[i]->Draw(&painter);
        }
    }

    for (int i = 0; i < enemyMissles.size(); i++)
    {
        if (enemyMissles[i] != nullptr)
        {
            enemyMissles[i]->Draw(&painter);
        }
    }

    for (int i = 0; i < friendlyMissles.size(); i++)
    {
        if (friendlyMissles[i] != nullptr)
        {
            friendlyMissles[i]->Draw(&painter);
        }
    }

    QString ScoreString = QString("Счёт: %1").arg(score);
    painter.setFont(QFont("Arial", 20));
    painter.drawText(10, 590, ScoreString);
}


void MainWindow::Update()
{
    EnemySpawner();
    enemySpawnDelay--;
    newEarth->Move();

    if (newMeteorite)
    {
        newMeteorite->Move();

        if (newMeteorite->GetMeteoriteBotoomY() >= newEarth->GetY())
        {
            DeleteMeteorite();
        }
    }

    QPoint cursorPosition = QWidget::mapFromGlobal(QCursor::pos());

    newJet->Move(cursorPosition.y());

    for (int i = 0; i < bombersVector.size(); i++)
    {
        if (bombersVector[i] != nullptr)
        {
            bombersVector[i]->Move();

            if (bombersVector[i]->GetRightX() <= 0)
            {
                DeleteBomber(i);
            }
        }
    }

    for (int i = 0; i < birdsVector.size(); i++)
    {
        if (birdsVector[i] != nullptr)
        {
            birdsVector[i]->Move();

            if (birdsVector[i]->GetRightX() <= 0)
            {
                DeleteBird(i);
            }
        }
    }

    for (int i = 0; i < enemyJetsVector.size(); i++)
    {
        if (enemyJetsVector[i] != nullptr)
        {
            enemyJetsVector[i]->Move();

            if (enemyJetsVector[i]->GetGunCoolDown() == 0)
            {
                enemyMissles.append(new EnemyMissle(enemyJetsVector[i]->GetXForMissle(), enemyJetsVector[i]->GetYForMissle()));
                enemyJetsVector[i]->SetIsGunFired(true);
            }

            if (enemyJetsVector[i]->GetRightX() <= 0)
            {
                DeleteEnemyJet(i);
            }
        }
    }

    for (int i = 0; i < friendlyMissles.size(); i++)
    {
        if (friendlyMissles[i] != nullptr)
        {
            friendlyMissles[i]->Move();
            if (friendlyMissles[i]->GetX() >= QWidget::size().width())
            {
                DeleteMissle(i);
            }
        }
    }

    for (int i = 0; i < enemyMissles.size(); i++)
    {
        if (enemyMissles[i] != nullptr)
        {
            enemyMissles[i]->Move();
            if (enemyMissles[i]->GetRightX() <= 0)
            {
                DeleteEnemyMissle(i);
            }
        }
    }

    if (fireSpeed != defaultFireSpeed)
    {
        fireSpeed++;
    }

    Collision();

    Hit();

    if (newMeteorite)
    {
        MeteoriteCollision();
    }

    WinFunction();

    repaint();
}


void MainWindow::GameOverFunction()
{
    QMessageBox::information(this, "ABC", "Game Over");
    QApplication::exit();
}


void MainWindow::WinFunction()
{
    if (score >= defaultWinCondition)
    {
        QMessageBox::information(this, "ABC", "You Won!");
        QApplication::exit();
    }
}


void MainWindow::Collision()
{
    if (newJet->GetBottomY() >= newEarth->GetY())
    {
        GameOverFunction();
    }
    else if (newMeteorite && newJet->GetJetRect().intersects(newMeteorite->GetMeteoriteRect()))
    {
        GameOverFunction();
    }

    for (int i = 0; i < birdsVector.size(); i++)
    {
        if (birdsVector[i] != nullptr)
        {
            if (newJet->GetJetRect().intersects(birdsVector[i]->GetBirdRect()))
            {
                birdsVector[i]->Move();
                GameOverFunction();
            }
        }
    }

    for (int i = 0; i < bombersVector.size(); i++)
    {
        if (bombersVector[i] != nullptr)
        {
            if (bombersVector[i]->CheckCollision(newJet->GetJetRect()))
            {
                bombersVector[i]->Move();
                GameOverFunction();
            }
        }
    }

    for (int i = 0; i < enemyJetsVector.size(); i++)
    {
        if (enemyJetsVector[i] != nullptr)
        {
            if (newJet->GetJetRect().intersects(enemyJetsVector[i]->GetJetRect()))
            {
                enemyJetsVector[i]->Move();
                GameOverFunction();
            }
        }
    }

    for (int j = 0; j < enemyMissles.size(); j++)
    {
        if (enemyMissles[j] != nullptr)
        {
            if (enemyMissles[j]->GetMissleRect().intersects(newJet->GetJetRect()))
            {
                GameOverFunction();
            }
        }
    }
}


void MainWindow::MeteoriteCollision()
{
    bool isDeleted = false;

    for (int j = 0; j < enemyJetsVector.size(); j++)
    {
        if (enemyJetsVector[j] != nullptr)
        {
            if (newMeteorite->GetMeteoriteRect().intersects(enemyJetsVector[j]->GetJetRect()))
            {
                DeleteMeteorite();
                DeleteEnemyJet(j);
                isDeleted = true;
                break;
            }
        }
    }

    for (int j = 0; j < bombersVector.size(); j++)
    {
        if (isDeleted)
        {
            break;
        }

        if (bombersVector[j] != nullptr)
        {
            if (bombersVector[j]->CheckCollision(newMeteorite->GetMeteoriteRect()))
            {
                DeleteMeteorite();
                DeleteBomber(j);
                isDeleted = true;
                break;
            }
        }
    }

    for (int j = 0; j < enemyMissles.size(); j++)
    {
        if (isDeleted)
        {
            break;
        }

        if (enemyMissles[j] != nullptr)
        {
            if (newMeteorite->GetMeteoriteRect().intersects(enemyMissles[j]->GetMissleRect()))
            {
                DeleteEnemyMissle(j);
                DeleteMeteorite();
                isDeleted = true;
                break;
            }
        }
    }
}


void MainWindow::Hit()
{
    bool flagToBreak = false;

    for (int i = 0; i < friendlyMissles.size(); i++)
    {
        if (friendlyMissles[i] != nullptr)
        {
            if (newMeteorite && friendlyMissles[i]->GetMissleRect().intersects(newMeteorite->GetMeteoriteRect()))
            {
                score += 2;
                DeleteMeteorite();
                DeleteMissle(i);
                break;
            }

            for (int j = 0; j < enemyJetsVector.size(); j++)
            {
                if (enemyJetsVector[j] != nullptr)
                {
                    if (friendlyMissles[i]->GetMissleRect().intersects(enemyJetsVector[j]->GetJetRect()))
                    {
                        score += 5;
                        DeleteEnemyJet(j);

                        flagToBreak = true;
                        break;
                    }
                }
            }

            for (int j = 0; j < bombersVector.size(); j++)
            {
                if (bombersVector[j] != nullptr)
                {
                    if (bombersVector[j]->CheckCollision(friendlyMissles[i]->GetMissleRect()))
                    {
                        score += 10;
                        DeleteBomber(j);

                        flagToBreak = true;
                        break;
                    }
                }
            }

            for (int j = 0; j < enemyMissles.size(); j++)
            {
                if (enemyMissles[j] != nullptr)
                {
                    if (friendlyMissles[i]->GetMissleRect().intersects(enemyMissles[j]->GetMissleRect()))
                    {
                        score += 1;
                        DeleteEnemyMissle(j);

                        flagToBreak = true;
                        break;
                    }
                }
            }

            if (flagToBreak)
            {
                DeleteMissle(i);
                break;
            }
        }
    }
}


void MainWindow::DeleteMissle(int index)
{
    delete friendlyMissles[index];
    friendlyMissles[index] = nullptr;
    friendlyMissles.removeAt(index);
}


void MainWindow::DeleteEnemyMissle(int index)
{
    delete enemyMissles[index];
    enemyMissles[index] = nullptr;
    enemyMissles.removeAt(index);
}


void MainWindow::DeleteBird(int index)
{
    delete birdsVector[index];
    birdsVector[index] = nullptr;
    birdsVector.removeAt(index);
}


void MainWindow::DeleteBomber(int index)
{
    delete bombersVector[index];
    bombersVector[index] = nullptr;
    bombersVector.removeAt(index);
}


void MainWindow::DeleteEnemyJet(int index)
{
    delete enemyJetsVector[index];
    enemyJetsVector[index] = nullptr;
    enemyJetsVector.removeAt(index);
}


void MainWindow::DeleteMeteorite()
{
    delete newMeteorite;
    newMeteorite = nullptr;
}


void MainWindow::EnemySpawner()
{
    if (enemySpawnDelay == 0)
    {
        int randomEnemy = QRandomGenerator::global()->bounded(3);

        if (randomEnemy == 0)
        {
            birdsVector.append(new Bird());
        }
        else if (randomEnemy == 1)
        {
            enemyJetsVector.append(new EnemyJet());
        }
        else
        {
            bombersVector.append(new Bomber());
        }

        if (score < 25)
        {
            enemySpawnDelay = 30;
        }
        else if (score >= 25 && score < 50)
        {
            enemySpawnDelay = 20;
        }
        else
        {
            enemySpawnDelay = 10;
        }

        if (!newMeteorite)
        {
            newMeteorite = new Meteorite();
        }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

