#include "enemyview.h"
#include <QTimer>


EnemyView::EnemyView()
{
    setPixmap(QPixmap(":/images/ENERMY_1_down_1.png").scaled(50,50,Qt::KeepAspectRatio));
    nrOfPic = 4;
    timer = new QTimer();
    timerDeath = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(updates()));
    connect(timerDeath, SIGNAL(timeout()), this, SLOT(updatesDeath()));
    timer->start(120);
}

EnemyView::~EnemyView()
{
    delete timerDeath;
    delete timer;
}

//animation
void EnemyView::updates()
{
    switch (nrOfPic) {
    case 1:{
        setPixmap(QPixmap(":/images/ENERMY_1_down_1.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic=4;
        break;
    }
    case 2:{
        setPixmap(QPixmap(":/images/ENERMY_1_down_4.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic-=1;
        break;
    }
    case 3:{
        setPixmap(QPixmap(":/images/ENERMY_1_down_3.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic-=1;
        break;
    }
    case 4:{
        setPixmap(QPixmap(":/images/ENERMY_1_down_2.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic-=1;
        break;
    }
    }
}

void EnemyView::updatesDeath()
{
    switch (nrOfPic) {
    case 1:{
        setPixmap(QPixmap(":/images/NORMAL_DEATH_1.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic=3;
        break;
    }
    case 2:{
        setPixmap(QPixmap(":/images/NORMAL_DEATH_3.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic-=1;
        break;
    }
    case 3:{
        setPixmap(QPixmap(":/images/NORMAL_DEATH_2.png").scaled(50,50,Qt::KeepAspectRatio));
        nrOfPic-=1;
        break;
    }
    }
}

void EnemyView::dead_slot()
{
    timer->stop();
    nrOfPic = 3;
    timerDeath->start(120);
}

